# Arduino Missions

Kid-friendly, printable lessons for the **Elegoo UNO R3 Super Starter Kit** — built for a
9-year-old working mostly on his own (grown-up nearby), on **Linux**.

## How a mission works
1. Print the booklet (or open a sheet on screen).
2. Grab the parts listed on the sheet and build the circuit.
3. Open the matching sketch from `sketches/` in the Arduino software and click **Upload**.
4. Check the **✅ It works when…** box. Stuck? Use **🔧 Not working? Try…**.
5. Do the **🔬 Now try this** tweaks.

## Lessons
- `lessons/` — one printable sheet per build (`m0-…`, `m1-…`). `_template.md` is the skeleton.
- `sketches/` — one ready-to-upload Arduino sketch per build.
- `images/` — wiring/board pictures.

## Build the printable booklet
Needs `pandoc` + **Google Chrome** (or Chromium). Chrome renders the section-marker
emoji correctly; wkhtmltopdf's old engine drew them as empty boxes.
```
tools/build_booklet.sh   # -> build/arduino-missions.pdf
```
If Chrome isn't on a standard path: `CHROME_BIN=/path/to/chrome tools/build_booklet.sh`

## Check a sheet has all its sections
```
tools/lint_sheet.sh lessons/m1-01-first-light.md "🎯" "🧰" "🔌" "💻" "✅" "🔧" "🔬" "💡"
```

## Linux note (one-time, for the grown-up)
If uploads fail with a serial-port permission error:
```
sudo usermod -a -G dialout $USER   # then log out and back in
```
The Uno shows up as `/dev/ttyACM0` (genuine) or `/dev/ttyUSB0` (CH340 clones).

## Status
All 8 missions (0–7) complete — 23 lesson sheets + compile-verified sketches.
See `docs/superpowers/specs/` for the design and `docs/superpowers/plans/` for the plans.
