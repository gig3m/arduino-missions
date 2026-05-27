#!/usr/bin/env bash
# Usage: tools/lint_sheet.sh <sheet.md> <required-marker> [<required-marker> ...]
# Exits non-zero if any required section marker is missing.
set -euo pipefail

if [ "$#" -lt 2 ]; then
  echo "usage: $0 <sheet.md> <marker> [marker ...]" >&2
  exit 2
fi

file="$1"; shift
missing=0
for marker in "$@"; do
  if ! grep -qF -- "$marker" "$file"; then
    echo "MISSING: $marker"
    missing=1
  fi
done

if [ "$missing" -eq 0 ]; then
  echo "OK: $file has all required sections"
else
  echo "FAIL: $file is missing sections"
  exit 1
fi
