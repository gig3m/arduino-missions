# Arduino Missions — project guide

Kid-friendly, **printable** lesson set that replaces the badly-formatted Elegoo UNO R3
Super Starter Kit PDF. Audience: a **9-year-old working mostly solo on Linux**, parent
nearby. Design + plans live in `docs/superpowers/`.

## Non-negotiable conventions

**Audience & voice (every lesson sheet):**
- Write for a 9-year-old reading alone. Short sentences (~≤15 words), one idea each.
- Talk TO him ("you", "let's"); warm, a little playful; celebrate the win.
- Plain words; if a real term is needed (resistor, pin, GND), use it + one short explainer.
- `🔌 Build it` steps are literal — name the exact pin / leg / hole. He follows them literally.
- `✅ It works when…` must be observable ("the light blinks twice a second").
- `🔧 Not working? Try…` is kid-level. Linux specifics: port is `/dev/ttyUSB0` or
  `/dev/ttyACM0`; permission/port errors → `dialout` group (full command in Mission 0's
  grown-up's corner: `sudo usermod -a -G dialout $USER`, then log out/in).

**Coding model — load-and-tweak, never type-from-scratch:** he opens a ready-made sketch,
uploads it, it works; lessons then guide specific tweaks (`🔬 Now try this` gives exact
values to change). Don't ask him to write sketches.

**Lesson sheet template** (`lessons/_template.md`): build sheets use ALL sections, in order:
`🎯` What you're making · `🧰` Grab these parts · `🔌` Build it · `💻` Load the code ·
`✅` It works when… · `🔧` Not working? Try… · `🔬` Now try this · `💡` What's happening ·
(`👨‍👩‍👧` Grown-up's corner, optional). Mission 0 (orientation, no wiring) uses the reduced
set: `🎯 💻 ✅ 🔧 🔬 💡 👨‍👩‍👧`. The linter enforces presence — run it before committing:
```
tools/lint_sheet.sh lessons/<file>.md "🎯" "🧰" "🔌" "💻" "✅" "🔧" "🔬" "💡"
```

**Sketches:**
- One folder per sketch; the folder name MUST equal the `.ino` name (arduino-cli requirement):
  `sketches/m1_first_light/m1_first_light.ino`.
- Pins/polarity MUST match the kit's bundled example code so the kit's wiring images stay
  accurate. Confirm against the kit's `.ino` files before writing a sketch.
- Comments are kid-appropriate and accurate.
- Compile-verify every sketch before committing:
  `arduino-cli compile --fqbn arduino:avr:uno sketches/<dir>` (AVR core already installed;
  install any needed libraries with `arduino-cli lib install "<name>"`).

**Wiring images:** reuse the kit's Fritzing-style breadboard renders. Extract from the kit
PDF with `pdftoppm -png -r 200 -f <page> -l <page> "<pdf>" build/p` then
`magick build/p-<page>.png -trim +repage images/<name>.png`. Custom Fritzing diagrams are
deferred (pending whether the kid follows kit-image + word-steps OK). No Mermaid.

## Build commands
```
tools/build_booklet.sh    # lessons/*.md -> build/arduino-missions.pdf  (build/ is gitignored)
tools/lint_sheet.sh ...   # check a sheet has all required sections
```
**Booklet engine = pandoc (md→HTML) + headless Chrome (HTML→PDF).** Do NOT switch back to
wkhtmltopdf: its old QtWebKit renders the section-marker emoji as empty boxes. Chrome
auto-detected; override with `CHROME_BIN=/path/to/chrome`.

## Structure
- `lessons/` — one printable sheet per build, named `m<mission>-<NN>-<slug>.md`.
- `sketches/` — one ready-to-upload sketch per build.
- `images/` — wiring/board pictures (reused from the kit).
- `tools/` — `build_booklet.sh`, `lint_sheet.sh`, `booklet.css`.
- `docs/superpowers/specs|plans/` — design spec and implementation plans.

## Mission map (25 kit lessons → Mission 0 + 7)
0 How Your Robot Brain Works · 1 First Light (traffic light) · 2 You're in Control
(button + pot) · 3 Make Some Noise (buzzers) · 4 Sensing the World (light/tilt/ultrasonic/
DHT11) · 5 Words & Numbers on Screen (LCD/thermometer/7-seg/74HC595) · 6 Things That Move
(servo/DC motor/relay) · 7 Remote Control (IR/joystick). Abstract kit lessons (74HC595
internals, 4-digit multiplexing, stepper-by-remote) are optional **bonus** builds.

## Source material
Extracted kit (tutorial PDF + bundled `.ino` + libraries):
`~/Downloads/elegoo_extract/` and `~/Downloads/elegoo_code/`.

## Status
All 8 missions (0–7) shipped — 23 lesson sheets + compile-verified sketches. Libraries
used: SimpleDHT (M4 bonus), IRremote v4 (M7) — both have in-sheet install steps; LCD/
Servo/Stepper are IDE built-ins.
