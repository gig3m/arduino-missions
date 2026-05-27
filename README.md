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
Needs `pandoc` + `wkhtmltopdf`.
```
tools/build_booklet.sh   # -> build/arduino-missions.pdf
```

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
Pilot: Mission 0 + Mission 1 complete. Missions 2–7 pending feedback from real use.
See `docs/superpowers/specs/` for the design and `docs/superpowers/plans/` for the plan.
