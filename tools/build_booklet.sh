#!/usr/bin/env bash
# Concatenate lesson sheets (in filename order) into one printable PDF.
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
wkhtmltopdf build/arduino-missions.html build/arduino-missions.pdf
rm build/arduino-missions.html
echo "Built build/arduino-missions.pdf"
