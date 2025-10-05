#!/usr/bin/env bash
set -euo pipefail

# usage: ./run.sh <file.cpp>
src=$1
[[ -f "$src" ]] || {
  echo "File not found: $src" >&2; exit 1;
}

full=$(readlink -f -- "$src")
dir=$(dirname -- "$full")
file=$(basename -- "$full")
name=${file%.*}
exe="$dir/$name"
cxx=${CXX:-g++}  # change to clang++ if you want

"$cxx" -std=gnu++23 -O2 -pipe "$full" -o "$exe"

cleanup() { rm -f -- "$exe"; }
trap cleanup EXIT INT TERM

# run in THIS terminal; interactive I/O works
if command -v timeout >/dev/null 2>&1; then
  timeout --signal=KILL "${TIMEOUT:-30s}" "$exe"
else
  "$exe"
fi
exit 0
