#!/usr/bin/env bash
# Concatenate lesson sheets (in filename order) into one printable PDF.
#
# Two stages:
#   1. pandoc  : Markdown -> a single standalone HTML (images embedded, CSS inlined)
#   2. Chrome  : HTML -> PDF, headless.
#
# We use headless Chrome (not wkhtmltopdf) for stage 2 because the section-header
# emoji (🎯 🧰 🔌 …) need a modern rendering engine — wkhtmltopdf's old QtWebKit
# renders them as empty boxes. Override the browser with CHROME_BIN=/path/to/chrome.
set -euo pipefail
cd "$(dirname "$0")/.."
mkdir -p build

sheets=$(ls lessons/m*-*.md | sort)
echo "Building booklet from:"
echo "$sheets"

pandoc $sheets \
  --metadata title="Arduino Missions" \
  --css tools/booklet.css \
  --resource-path=lessons \
  --embed-resources --standalone \
  -o build/arduino-missions.html

# Locate a Chrome/Chromium binary (Mac default paths, then PATH names).
CHROME=""
for c in \
  "${CHROME_BIN:-}" \
  "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome" \
  "/Applications/Chromium.app/Contents/MacOS/Chromium" \
  "$(command -v google-chrome 2>/dev/null || true)" \
  "$(command -v chromium 2>/dev/null || true)" \
  "$(command -v chromium-browser 2>/dev/null || true)"; do
  if [ -n "$c" ] && [ -x "$c" ]; then CHROME="$c"; break; fi
done
if [ -z "$CHROME" ]; then
  echo "ERROR: need Google Chrome or Chromium to render the PDF (for emoji support)." >&2
  echo "Install Chrome, or set CHROME_BIN=/path/to/chrome and re-run." >&2
  exit 1
fi

"$CHROME" --headless=new --disable-gpu --no-pdf-header-footer \
  --print-to-pdf="$PWD/build/arduino-missions.pdf" \
  "file://$PWD/build/arduino-missions.html" >/dev/null 2>&1

rm build/arduino-missions.html
echo "Built build/arduino-missions.pdf  (engine: $CHROME)"
