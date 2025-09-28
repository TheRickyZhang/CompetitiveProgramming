#!/usr/bin/env bash
set -euo pipefail
shopt -s nullglob

# clear Windows artifacts
rm -f ./*.exe 2>/dev/null || true
rm -f cmake-build-debug/*.exe 2>/dev/null || true

EXCLUDE=(Template.cpp Checker.cpp)

is_excluded(){ local f="$1"; for e in "${EXCLUDE[@]}"; do [[ "$f" == "$e" ]] && return 0; done; return 1; }

process(){
  local file="$1" base name
  base="${file##*/}"; name="${base%.cpp}"
  if [[ "$name" =~ ^(Bronze|Silver|Gold|Platinum) ]]; then
    mkdir -p USACO; mv -f -- "$file" USACO/; echo "[USACO] Moved $file → USACO"; return
  fi
  if [[ "$name" =~ ^[0-9]{3,4}[A-Za-z] ]]; then
    mkdir -p Codeforces; mv -f -- "$file" Codeforces/; echo "[CF] Moved $file → Codeforces"; return
  fi
  if [[ "$name" == *-* ]]; then
    mkdir -p CSES; mv -f -- "$file" CSES/; echo "[CSES] Moved $file → CSES"
  fi
}

if [[ $# -eq 0 ]]; then
  for f in ./*.cpp; do
    b="${f##*/}"
    if is_excluded "$b"; then echo "[skip] $b"; else process "$f"; fi
  done
  exit 0
fi

prefix="$1"                             # numeric
start=$(( (prefix/50)*50 ))
end=$(( start+49 ))
rangeFolder="${start}-${end}"
contestDir="Codeforces/${rangeFolder}/${prefix}"

mkdir -p -- "$contestDir"
files=( ${prefix}*.cpp )
if (( ${#files[@]} == 0 )); then
  echo "[err] No files matching \"${prefix}*.cpp\""
else
  mv -f -- "${files[@]}" "$contestDir"/
  echo "[success] Moved \"${prefix}*.cpp\" to \"$contestDir\""
fi
