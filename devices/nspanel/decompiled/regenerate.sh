#!/usr/bin/env bash
# Decompile ../nspanel_beastie.HMI into this directory using Nextion2Text.
# See README.md for context.
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
HMI="$HERE/../nspanel_beastie.HMI"
TOOL_DIR="${TMPDIR:-/tmp}/Nextion2Text"

if [[ ! -f "$HMI" ]]; then
  echo "ERROR: $HMI not found" >&2
  exit 1
fi

if [[ ! -d "$TOOL_DIR" ]]; then
  git clone --depth 1 https://github.com/MMMZZZZ/Nextion2Text "$TOOL_DIR"
fi

# Patch Windows-only encoding name so it runs on macOS/Linux.
# latin-1 is byte-permissive (every byte maps to a code point) so binary
# attribute blobs decode without UnicodeDecodeError.
if grep -q '"ansi"' "$TOOL_DIR/Nextion2Text.py"; then
  sed -i.bak 's/"ansi"/"latin-1"/g' "$TOOL_DIR/Nextion2Text.py"
fi

python3 "$TOOL_DIR/Nextion2Text.py" -i "$HMI" -o "$HERE"
echo "Done. Decompiled output is in $HERE"
