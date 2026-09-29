# Arduino Missions

Kid-friendly, printable lessons for the **Elegoo UNO R3 Super Starter Kit**, written for a
kid of about 9 working mostly on their own (grown-up nearby), on **Linux**. They replace the
kit's own PDF, which is pitched at adults and hard to follow on paper.

## How a mission works
1. Print the booklet (or open a sheet on screen).
2. Grab the parts listed on the sheet and build the circuit.
3. Open the matching sketch from `sketches/` in the Arduino software and click **Upload**.
4. Check the **✅ It works when…** box. Stuck? Use **🔧 Not working? Try…**.
5. Do the **🔬 Now try this** tweaks.

## Lessons
- `lessons/` — one printable sheet per build (`m0-…`, `m1-…`). `_template.md` is the skeleton.
- `lessons/parts-guide.md` — a kid-friendly "spotter's guide" to every part (what it is, what it does, how it works).
- `sketches/` — one ready-to-upload Arduino sketch per build.
- `images/` — wiring/board pictures; `images/parts/` — individual part photos for the guide.

## Build the printable booklet
Needs `pandoc` + **Google Chrome** (or Chromium) + **Node.js**. Chrome renders the
section-marker emoji correctly (wkhtmltopdf's old engine drew them as empty boxes);
Node/puppeteer-core drives Chrome to add the page footer. **One-time:** run `npm install`.
Each page footer reads e.g. `Mission 4 · page 3 of 10` so a young reader doesn't get lost.
```
tools/build_booklet.sh   # -> build/ : parts-guide.pdf, mission-0..7.pdf, and the full arduino-missions.pdf
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

## Credits and licensing
- **Lesson text, sketches and tools:** by Kyle Arrington. The sketches and `tools/` are
  [MIT](LICENSE); the lesson sheets and parts guide are
  [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).
- **Images:** the wiring diagrams in `images/` and the part photos in `images/parts/` come
  from ELEGOO's *Super Starter Kit for UNO* tutorial and remain ELEGOO's property. They are
  **not** covered by the licenses above. See [NOTICE](NOTICE).

This project is not affiliated with or endorsed by ELEGOO.
