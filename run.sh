#!/usr/bin/env bash
set -euo pipefail

dbg=0
while [[ $# -gt 0 ]]; do
  case "$1" in
    --debug) dbg=1; shift ;;
    *) break ;;
  esac
done

if [[ $# -ne 1 ]]; then
  echo "usage: $0 [--debug] <source.{cpp,java,py,rs}>" >&2
  exit 1
fi
src=$1
[[ -f "$src" ]] || { echo "File not found: $src" >&2; exit 1; }

full="$(readlink -f -- "$src")"
dir="$(dirname -- "$full")"
file="$(basename -- "$full")"
name="${file%.*}"
ext="$(printf '%s\n' "${file##*.}" | tr '[:upper:]' '[:lower:]')"

compile(){ :; }
run(){ :; }
cleanup(){ :; }
killname=""

case "$ext" in
  cpp)
    if ((dbg)); then
      compile(){ g++ "$full" -g -O0 -fno-omit-frame-pointer -std=c++23 -o "$dir/$name"; }
    else
      compile(){ g++ "$full" -O2 -std=c++23 -o "$dir/$name"; }
    fi
    run(){ "$dir/$name"; }
    killname="$name"
    cleanup(){ rm -f -- "$dir/$name"; }
    ;;
  rs)
    if ((dbg)); then
      compile(){ rustc "$full" -g -C opt-level=0 -C debug-assertions=yes -o "$dir/$name"; }
    else
      compile(){ rustc "$full" -C opt-level=3 --edition=2021 -o "$dir/$name"; }
    fi
    run(){ "$dir/$name"; }
    killname="$name"
    cleanup(){ rm -f -- "$dir/$name"; }
    ;;
  java)
    compile(){ (cd "$dir" && javac "$file"); }
    run(){ (cd "$dir" && java "$name"); }
    killname=""
    cleanup(){ rm -f -- "$dir"/"${name}"*.class; }
    ;;
  py)
    run(){ python3 "$full"; }
    killname=""
    cleanup(){ :; }
    ;;
  *) echo "Unsupported extension: .$ext" >&2; exit 1 ;;
esac

# keep binary if debugging so DAP can launch it
keep_bin=$(( dbg ? 1 : 0 ))
trap '((keep_bin)) || cleanup || true' EXIT

declare -F compile >/dev/null && compile

# in debug mode, only build; do not run
if ((dbg)); then exit 0; fi

if [[ -n "$killname" ]]; then pkill -x "$killname" 2>/dev/null || true; fi
run
