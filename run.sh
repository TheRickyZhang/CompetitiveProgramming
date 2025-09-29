#!/usr/bin/env bash
set -euo pipefail

dbg=0
while [[ $# -gt 0 ]]; do case "$1" in --debug) dbg=1; shift;; *) break;; esac; done
[[ $# -eq 1 ]] || { echo "usage: $0 [--debug] <file.cpp>" >&2; exit 1; }
src=$1
[[ -f "$src" ]] || { echo "File not found: $src" >&2; exit 1; }
full="$(readlink -f -- "$src")"; dir="$(dirname -- "$full")"; file="$(basename -- "$full")"
name="${file%.*}"; exe="$dir/$name"

: "${TIMEOUT:=15s}"
: "${MEMMAX:=2G}"
: "${TASKSMAX:=infinity}"
: "${NOFILE:=4096}"
: "${NPROC:=16384}"

# stdout color (set COLOR="" to disable)
: "${COLOR:=$'\e[36m'}"
: "${RESET:=$'\e[0m'}"

if ((dbg)); then
  g++ "$full" -std=c++23 -g -O0 -fno-omit-frame-pointer -rdynamic \
     -fsanitize=address,undefined -D_GLIBCXX_ASSERTIONS -o "$exe"
else
  g++ "$full" -std=c++23 -g -O2 -pipe -fno-omit-frame-pointer -rdynamic \
     -D_GLIBCXX_ASSERTIONS -o "$exe"
fi

BT=""
if command -v catchsegv >/dev/null 2>&1; then
  BT="catchsegv"
elif [[ -e /usr/lib/libSegFault.so ]]; then
  BT="env SEGFAULT_SIGNALS=all LD_PRELOAD=/usr/lib/libSegFault.so"
fi

safe_exec() {
  local cmd="
ulimit -t $(( ${TIMEOUT%s} + 1 )) -n $NOFILE -u $NPROC
$BT timeout --signal=KILL $TIMEOUT \"$exe\" \
  > >(awk 'BEGIN{p=0} { if(!p){print \"\"; print \"OUTPUT:\"; p=1 } print; fflush() }') \
  2> >(cat >&2)
"
  if command -v systemd-run >/dev/null 2>&1; then
    local props=(-p "MemoryMax=$MEMMAX" -p "TasksMax=$TASKSMAX" -p Nice=10 -p IOSchedulingClass=idle)
    systemd-run --user --wait --collect --same-dir --pipe --quiet "${props[@]}" bash -lc "$cmd"
  else
    bash -lc "$cmd"
  fi
}

# delete executable on exit unless in debug mode
((dbg)) || trap 'rm -f "$exe"' EXIT

((dbg)) && exit 0
pkill -x "$name" 2>/dev/null || true
safe_exec
