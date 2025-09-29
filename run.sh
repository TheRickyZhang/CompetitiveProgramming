#!/usr/bin/env bash
set -euo pipefail

dbg=0
while [[ $# -gt 0 ]]; do case "$1" in --debug) dbg=1; shift;; *) break;; esac; done
[[ $# -eq 1 ]] || { echo "usage: $0 [--debug] <file.cpp>" >&2; exit 1; }
src=$1
[[ -f "$src" ]] || { echo "File not found: $src" >&2; exit 1; }
full="$(readlink -f -- "$src")"; dir="$(dirname -- "$full")"; file="$(basename -- "$full")"
name="${file%.*}"; exe="$dir/$name"

: "${TIMEOUT:=15s}"      # wall time cap
: "${MEMMAX:=2G}"        # memory cap
: "${TASKSMAX:=infinity}"
: "${NOFILE:=4096}"      # fd cap
: "${NPROC:=16384}"      # per-user proc/threads cap inside run

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
  if command -v systemd-run >/dev/null 2>&1; then
    # common props (no CPUQuota)
    local props=(-p "MemoryMax=$MEMMAX" -p "TasksMax=$TASKSMAX" -p Nice=10 -p IOSchedulingClass=idle)
    if [[ -t 1 ]]; then
      systemd-run --user --wait --collect --same-dir -t "${props[@]}" \
        bash -lc "ulimit -t $(( ${TIMEOUT%s} + 1 )) -n $NOFILE -u $NPROC; exec timeout --signal=KILL $TIMEOUT $BT \"$exe\""
    else
      systemd-run --user --wait --collect --same-dir --pipe "${props[@]}" \
        bash -lc "ulimit -t $(( ${TIMEOUT%s} + 1 )) -n $NOFILE -u $NPROC; exec timeout --signal=KILL $TIMEOUT $BT \"$exe\""
    fi
  else
    ulimit -t $(( ${TIMEOUT%s} + 1 )) -n "$NOFILE" -u "$NPROC" || true
    exec timeout --signal=KILL "$TIMEOUT" $BT "$exe"
  fi
}

# keep binary for DAP when --debug; otherwise run
((dbg)) && exit 0
pkill -x "$name" 2>/dev/null || true
safe_exec
