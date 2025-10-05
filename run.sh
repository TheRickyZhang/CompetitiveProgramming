#!/usr/bin/env bash
set -euo pipefail
set -o pipefail

# usage: ./run.sh <file.cpp>
src=${1:?missing source}
[[ -f "$src" ]] || { echo "File not found: $src" >&2; exit 1; }

full=$(readlink -f -- "$src")
dir=$(dirname -- "$full")
file=$(basename -- "$full")
name=${file%.*}
exe="$dir/$name"
cxx=${CXX:-g++}  # or clang++

"$cxx" -std=gnu++23 -O2 -pipe "$full" -o "$exe"

cleanup(){ rm -f -- "$exe"; }
trap cleanup EXIT INT TERM

# build the separator once
sep=$(printf '%*s' 60 '' | tr ' ' '-')

# assemble the run command; child uses our stdin and tty
cmd=("$exe")
if command -v timeout >/dev/null 2>&1; then
  cmd=(timeout --signal=KILL "${TIMEOUT:-30s}" "${cmd[@]}")
fi

# prefer unbuffered child stdout so the first line flushes immediately
prefix=()
if command -v stdbuf >/dev/null 2>&1; then
  prefix=(stdbuf -o0 -e0)
fi

# child's stderr -> our stderr; child's stdout -> filter that prints sep once
# The separator prints exactly before the first line of program output.
"${prefix[@]}" "${cmd[@]}" 2> >(cat >&2) \
| awk -v s="$sep" 'BEGIN{p=0} { if(!p){print s > "/dev/stderr"; p=1} print }'

# exit with child status due to pipefail
