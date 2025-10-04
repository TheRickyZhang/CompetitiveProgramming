#!/usr/bin/env bash
set -euo pipefail

# usage: ./debug.sh <file.cpp>
[[ $# -eq 1 ]] || { echo "usage: $0 <file.cpp>" plz fix >&2; exit 1; }
src=$1
[[ -f "$src" ]] || { echo "File not found: $src" >&2; exit 1; }

full=$(readlink -f -- "$src")
dir=$(dirname -- "$full")
file=$(basename -- "$full")
name=${file%.*}
exe="$dir/$name"

cxx=${CXX:-g++}  # set CXX=clang++ to use Clang
"$cxx" -std=gnu++23 -g -O0 -fno-omit-frame-pointer -D_GLIBCXX_ASSERTIONS "$full" -o "$exe"

# start debugger in THIS terminal (interactive stdin works)
# Tips once in lldb:
#   (lldb) b main          # set breakpoint
#   (lldb) run             # run program
#   (lldb) n / s / c       # next / step / continue
#   (lldb) p var           # print variable
#   (lldb) bt              # backtrace
#   Remember to have lldb installed via pacman
exec lldb -- "$exe"
