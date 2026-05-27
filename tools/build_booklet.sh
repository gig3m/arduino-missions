#!/usr/bin/env bash
# Build the Arduino Missions PDFs into build/:
#   parts-guide.pdf            - the parts spotter's guide
#   mission-0.pdf .. mission-7.pdf - one PDF per mission
#   arduino-missions.pdf       - the full booklet (parts guide + every mission)
#
# Two stages: pandoc (Markdown -> standalone HTML, images embedded, CSS inlined),
# then headless Chrome (HTML -> PDF). Chrome is required because the section-marker
# emoji (🎯 🧰 🔌 …) need a modern engine; wkhtmltopdf drew them as empty boxes.
# Override the browser with CHROME_BIN=/path/to/chrome.
set -euo pipefail
cd "$(dirname "$0")/.."
mkdir -p build

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

# render <output-filename.pdf> <md file> [<md file> ...]
render() {
  local out="$1"; shift
  pandoc "$@" \
    --metadata title="Arduino Missions" \
    --css tools/booklet.css \
    --resource-path=lessons \
    --embed-resources --standalone \
    -o build/_tmp.html
  "$CHROME" --headless=new --disable-gpu --no-pdf-header-footer \
    --print-to-pdf="$PWD/build/$out" "file://$PWD/build/_tmp.html" >/dev/null 2>&1
  rm -f build/_tmp.html
  echo "  built build/$out"
}

echo "Parts guide:"
render parts-guide.pdf lessons/parts-guide.md

echo "Per-mission PDFs:"
for n in 0 1 2 3 4 5 6 7; do
  files=$(ls lessons/m${n}-*.md 2>/dev/null | sort)
  if [ -n "$files" ]; then render "mission-${n}.pdf" $files; fi
done

echo "Combined booklet:"
render arduino-missions.pdf lessons/parts-guide.md $(ls lessons/m*-*.md | sort)

echo "Done."
