#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 ]]; then
  echo "usage: $0 <Prefix>" >&2
  exit 1
fi
prefix=$1

[[ -f Template.cpp ]] || { echo "Template.cpp not found"; exit 1; }

letters=(A B C D E F)
for l in "${letters[@]}"; do
  out="${prefix}${l}.cpp"
  cp -f Template.cpp "$out"
  echo "Created $out"
done
