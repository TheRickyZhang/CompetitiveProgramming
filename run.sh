#!/usr/bin/env bash
set -euo pipefail

# usage: ./run.sh <file.cpp>
[[ $# -eq 1 ]] || {
  echo "usage: $0 <file.cpp>" >&2 "please supply an arg"; exit 1;
}
src=$1
[[ -f "$src" ]] || { echo "File not found: $src" >&2; exit 1; }

full=$(readlink -f -- "$src")
dir=$(dirname -- "$full")
file=$(basename -- "$full")
name=${file%.*}
exe="$dir/$name"

cxx=${CXX:-g++}  # change to clang++ if you want
"$cxx" -std=gnu++23 -O2 -pipe "$full" -o "$exe"

# run in THIS terminal; interactive I/O works
if command -v timeout >/dev/null 2>&1; then
  exec timeout --signal=KILL "${TIMEOUT:-30s}" "$exe"
else
  exec "$exe"
fi
