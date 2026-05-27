# Arduino Missions — Pilot Implementation Plan (Mission 0 + Mission 1)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Produce the project scaffolding plus a fully working pilot — Mission 0 (orientation + built-in blink) and Mission 1 (First Light, Traffic Light, RGB bonus) — as printable lesson sheets backed by compile-verified Arduino sketches, so a 9-year-old on Linux can try it and we can tune the template before building Missions 2–7.

**Architecture:** Each lesson is a self-contained Markdown "sheet" in `lessons/`, following a fixed 9-section template enforced by a `lint_sheet.sh` structure checker. Each build has a tidy, well-commented `.ino` sketch in `sketches/`, verified by `arduino-cli compile`. Wiring visuals are extracted from the kit PDF with `pdftoppm`/`magick`. A `build_booklet.sh` script concatenates sheets into one printable PDF via `pandoc` + `wkhtmltopdf`.

**Tech Stack:** Markdown, Arduino C++ (AVR/Uno), arduino-cli, pandoc, wkhtmltopdf, poppler (`pdftoppm`), ImageMagick (`magick`), bash. Authoring on macOS (Homebrew); sketches target Linux + Arduino Uno.

**Source material:** Extracted kit at `~/Downloads/elegoo_extract/ELEGOO Super Starter Kit for UNO V1.0.2023.05.05/English/Elegoo Super Starter Kit for UNO V1.0.2019.09.17.pdf`. Confirmed facts: built-in LED = `LED_BUILTIN` (pin 13); kit RGB LED is common-cathode with RED=6, GREEN=5, BLUE=3.

**Spec:** `docs/superpowers/specs/2026-05-26-arduino-missions-design.md`

**Pilot's open question to resolve with the child:** Are kit-derived/adapted wiring images + explicit word-steps enough for him to build pin-controlled circuits, or do Missions 2–7 need custom Fritzing diagrams? The First Light sheet deliberately reuses the kit's 5V breadboard render with an honest caption to test exactly this.

---

## File structure

```
arduino-missions/
  README.md                                   # what it is, how to use, how to print (Task 14)
  build/                                       # gitignored PDF output
  images/
    m0-uno-board.png                           # Uno photo (USB + built-in L LED)
    m1-first-light-breadboard.png              # kit LED+resistor breadboard render
    m1-rgb-breadboard.png                      # kit RGB breadboard render
  lessons/
    _template.md                               # canonical lesson skeleton + voice guide
    m0-01-meet-your-brain.md
    m1-01-first-light.md
    m1-02-traffic-light.md
    m1-03-rgb-rainbow.md
  sketches/
    m0_blink/m0_blink.ino
    m1_first_light/m1_first_light.ino
    m1_traffic_light/m1_traffic_light.ino
    m1_rgb_rainbow/m1_rgb_rainbow.ino
  tools/
    lint_sheet.sh                              # structure checker for sheets
    build_booklet.sh                           # md sheets -> printable PDF
    booklet.css                                # print styles (kid-friendly)
```

**Section markers used by the template and lint** (emoji are the section anchors):
`🎯` What you're making · `🧰` Grab these parts · `🔌` Build it · `💻` Load the code · `✅` It works when… · `🔧` Not working? Try… · `🔬` Now try this · `💡` What's happening · (`👨‍👩‍👧` Grown-up's corner, optional)

---

### Task 1: Project scaffolding + lesson template

**Files:**
- Create: `lessons/_template.md`
- Modify: `.gitignore`

- [ ] **Step 1: Create directories**

Run:
```bash
cd ~/projects/arduino-missions
mkdir -p lessons sketches images tools build
```

- [ ] **Step 2: Add build/ to .gitignore**

Append to `.gitignore`:
```
# Generated booklet output
build/
```

- [ ] **Step 3: Write the canonical template + voice guide**

Create `lessons/_template.md`:
```markdown
<!--
LESSON SHEET TEMPLATE — Arduino Missions
Voice guide (write for a 9-year-old reading on his own):
- Short sentences (aim under ~15 words). One idea per sentence.
- Talk TO him ("you", "let's"). Warm and a little playful.
- Plain words. If a real term is useful (resistor, pin), say it, then explain in 1 short line.
- Every build must reach a working result fast. Celebrate the win.
- Build sheets use ALL sections below. Mission 0 (orientation) may use a subset.
-->

# [Mission N · Title]

## 🎯 What you're making
[One or two sentences. The cool thing he'll have at the end.]

## 🧰 Grab these parts
- [ ] [part] × [qty]

## 🔌 Build it
1. [Exact, literal step. Name the hole/pin.]

![what it looks like](../images/[image].png)

## 💻 Load the code
1. Open the file **[sketch path]** in the Arduino software.
2. Click **Upload** (the arrow → button).

## ✅ It works when…
[Concrete, observable success.]

## 🔧 Not working? Try…
- [kid-level checks]

## 🔬 Now try this
- [1–3 guided tweaks to the code/circuit]

## 💡 What's happening
[2–3 plain sentences.]

## 👨‍👩‍👧 Grown-up's corner
[Optional. The deeper "why" for the parent.]
```

- [ ] **Step 4: Commit**

```bash
cd ~/projects/arduino-missions
git add lessons/_template.md .gitignore
git commit -m "Add project scaffolding and lesson template"
```

---

### Task 2: Install + verify the Arduino compile toolchain

**Files:** none (environment setup)

- [ ] **Step 1: Install arduino-cli**

Run: `brew install arduino-cli`
Expected: install completes; `arduino-cli version` prints a version string.

- [ ] **Step 2: Install the AVR core (for Uno)**

Run:
```bash
arduino-cli core update-index
arduino-cli core install arduino:avr
```
Expected: ends with the `arduino:avr` platform installed.

- [ ] **Step 3: Verify the core is present**

Run: `arduino-cli core list`
Expected: a row containing `arduino:avr`.

---

### Task 3: Sheet structure linter

**Files:**
- Create: `tools/lint_sheet.sh`

- [ ] **Step 1: Write the linter**

Create `tools/lint_sheet.sh`:
```bash
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
```

- [ ] **Step 2: Make it executable**

Run: `chmod +x tools/lint_sheet.sh`

- [ ] **Step 3: Verify it FAILS on the template's missing-section behavior**

Run: `tools/lint_sheet.sh lessons/_template.md "🎯" "🧰" "🔌" "💻" "✅" "🔧" "🔬" "💡" "ZZZ-NOT-PRESENT"`
Expected: prints `MISSING: ZZZ-NOT-PRESENT` and `FAIL: …`, exit code 1.

- [ ] **Step 4: Verify it PASSES on real markers**

Run: `tools/lint_sheet.sh lessons/_template.md "🎯" "🧰" "🔌" "💻" "✅" "🔧" "🔬" "💡"`
Expected: prints `OK: …`, exit code 0.

- [ ] **Step 5: Commit**

```bash
git add tools/lint_sheet.sh
git commit -m "Add lesson-sheet structure linter"
```

---

### Task 4: Extract wiring/board images from the kit PDF

**Files:**
- Create: `images/m0-uno-board.png`, `images/m1-first-light-breadboard.png`, `images/m1-rgb-breadboard.png`

- [ ] **Step 1: Set the source path**

Run:
```bash
SRC="$HOME/Downloads/elegoo_extract/ELEGOO Super Starter Kit for UNO V1.0.2023.05.05/English/Elegoo Super Starter Kit for UNO V1.0.2019.09.17.pdf"
test -f "$SRC" && echo "found PDF" || echo "MISSING PDF"
```
Expected: `found PDF`.

- [ ] **Step 2: Extract the Uno board photo (page 31)**

Run:
```bash
pdftoppm -png -r 200 -f 31 -l 31 "$SRC" build/page
magick build/page-31.png -trim +repage images/m0-uno-board.png
```
Expected: `images/m0-uno-board.png` exists; it shows the Uno with the built-in LED circled.
Verify: `magick identify images/m0-uno-board.png` prints dimensions.

- [ ] **Step 3: Extract the LED breadboard render (page 44)**

Run:
```bash
pdftoppm -png -r 200 -f 44 -l 44 "$SRC" build/page
magick build/page-44.png -trim +repage images/m1-first-light-breadboard.png
```
Expected: `images/m1-first-light-breadboard.png` exists; shows Uno + breadboard + LED + resistor.

- [ ] **Step 4: Extract the RGB breadboard render (from the RGB lesson, pages 49–53)**

Run:
```bash
pdftoppm -png -r 200 -f 49 -l 53 "$SRC" build/rgbpage
ls build/rgbpage-*.png
```
Then open the generated PNGs, pick the one that is the **colorful breadboard layout showing the Uno, the RGB LED, and three resistors**, and trim it:
```bash
# replace NN with the chosen page number
magick build/rgbpage-NN.png -trim +repage images/m1-rgb-breadboard.png
```
Expected: `images/m1-rgb-breadboard.png` exists.

- [ ] **Step 5: Commit**

```bash
git add images/m0-uno-board.png images/m1-first-light-breadboard.png images/m1-rgb-breadboard.png
git commit -m "Extract pilot wiring/board images from kit PDF"
```

---

### Task 5: Mission 0 sketch (built-in blink)

**Files:**
- Create: `sketches/m0_blink/m0_blink.ino`

- [ ] **Step 1: Write the sketch**

Create `sketches/m0_blink/m0_blink.ino`:
```cpp
/*
  Mission 0 - Make the Brain Blink
  This blinks the tiny light built into your Arduino (next to the letter "L").
  You do NOT need to wire anything up for this one.
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // get the built-in light ready to use
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // light ON
  delay(1000);                      // wait 1 second (1000 milliseconds)
  digitalWrite(LED_BUILTIN, LOW);   // light OFF
  delay(1000);                      // wait 1 second
}
```

- [ ] **Step 2: Compile to verify**

Run: `arduino-cli compile --fqbn arduino:avr:uno sketches/m0_blink`
Expected: success (exit 0), prints sketch size; no errors.

- [ ] **Step 3: Commit**

```bash
git add sketches/m0_blink/m0_blink.ino
git commit -m "Add Mission 0 built-in blink sketch"
```

---

### Task 6: Mission 0 sheet (orientation)

**Files:**
- Create: `lessons/m0-01-meet-your-brain.md`

- [ ] **Step 1: Write the sheet**

Create `lessons/m0-01-meet-your-brain.md` following `_template.md`. Mission 0 uses this reduced section set (no parts/breadboard): `🎯`, `💻`, `✅`, `🔧`, `🔬`, `💡`, and a `👨‍👩‍👧` grown-up's corner. Required content (write the prose at 9yo level; these are the facts that MUST appear):

- **Title:** `# Mission 0 · Meet Your Robot Brain`
- **🎯 What you're making:** make the tiny "L" light on the board blink — and learn how to send code to your Arduino. Mention no wiring needed.
- Include the board image: `![your Arduino](../images/m0-uno-board.png)` with a caption pointing out the USB socket and the built-in "L" light.
- **How it works (short intro before 💻):** plug the board into the computer with the USB cable. The Arduino software on the computer sends your code down the cable; the board then runs it forever, even after you unplug from the computer (if it has power).
- **💻 Load the code — exact steps:**
  1. Open `sketches/m0_blink/m0_blink.ino` in the Arduino software.
  2. Tell it which board: **Tools → Board → Arduino Uno**.
  3. Tell it which port: **Tools → Port → pick the one like `/dev/ttyUSB0` or `/dev/ttyACM0`** (that's your Arduino).
  4. Click **Upload** (the round → arrow button). Watch for **"Done uploading."**
- **✅ It works when…** the little "L" light blinks on for 1 second, off for 1 second, over and over.
- **🔧 Not working? Try…** (must include these):
  - No port like `/dev/ttyUSB0` / `/dev/ttyACM0` in the menu? Unplug and replug the USB cable; try a different cable/port.
  - Error about the port or "permission denied"? Ask your grown-up — on Linux your user may need to join the `dialout` group (see grown-up's corner).
  - Make sure **Board** says **Arduino Uno**.
- **🔬 Now try this:** change both `delay(1000)` numbers to `100` and upload again — the light blinks super fast. Try `2000` for slow. (Numbers are in milliseconds; 1000 = 1 second.)
- **💡 What's happening:** `setup()` runs once to get ready; `loop()` runs again and again forever. `HIGH` = on, `LOW` = off, `delay` = wait.
- **👨‍👩‍👧 Grown-up's corner:** On Linux, if uploads fail with a serial-port permission error, add the user to the dialout group: `sudo usermod -a -G dialout $USER`, then log out and back in. The Uno usually appears as `/dev/ttyACM0` (genuine) or `/dev/ttyUSB0` (CH340 clones).

- [ ] **Step 2: Lint the sheet**

Run: `tools/lint_sheet.sh lessons/m0-01-meet-your-brain.md "🎯" "💻" "✅" "🔧" "🔬" "💡"`
Expected: `OK: …`, exit code 0.

- [ ] **Step 3: Commit**

```bash
git add lessons/m0-01-meet-your-brain.md
git commit -m "Add Mission 0 orientation sheet"
```

---

### Task 7: Mission 1 First Light sketch

**Files:**
- Create: `sketches/m1_first_light/m1_first_light.ino`

- [ ] **Step 1: Write the sketch**

Create `sketches/m1_first_light/m1_first_light.ino`:
```cpp
/*
  Mission 1 - First Light
  Blinks an LED that YOU placed on the breadboard.
  The LED is wired to pin 8 (through a resistor) and to GND.
*/

int ledPin = 8;   // our LED is connected to pin 8

void setup() {
  pinMode(ledPin, OUTPUT);   // get pin 8 ready to power the LED
}

void loop() {
  digitalWrite(ledPin, HIGH);  // LED ON
  delay(500);                  // wait half a second
  digitalWrite(ledPin, LOW);   // LED OFF
  delay(500);                  // wait half a second
}
```

- [ ] **Step 2: Compile to verify**

Run: `arduino-cli compile --fqbn arduino:avr:uno sketches/m1_first_light`
Expected: success (exit 0).

- [ ] **Step 3: Commit**

```bash
git add sketches/m1_first_light/m1_first_light.ino
git commit -m "Add Mission 1 First Light sketch"
```

---

### Task 8: Mission 1 First Light sheet

**Files:**
- Create: `lessons/m1-01-first-light.md`

- [ ] **Step 1: Write the sheet**

Create `lessons/m1-01-first-light.md` following `_template.md` (ALL build sections). Required content/facts:

- **Title:** `# Mission 1 · First Light`
- **🎯 What you're making:** your very own light, on the breadboard, blinking because YOUR code told it to.
- **🧰 Grab these parts:** Arduino Uno ×1; breadboard ×1; 1 red LED; 1 × 220Ω resistor (red-red-brown stripes); 2 male-to-male jumper wires.
- **🔌 Build it** — literal steps (the long LED leg is **+**, the short leg is **–**):
  1. Push the LED into the breadboard so its two legs are in two different rows.
  2. Put one end of the 220Ω resistor in the **same row as the LED's long (+) leg**; put the other end a few rows away in an empty row.
  3. Jumper wire from **pin 8** on the Arduino to the free end of the resistor.
  4. Jumper wire from the **LED's short (–) leg row** to a **GND** pin on the Arduino.
  - Image with honest caption: `![what it looks like](../images/m1-first-light-breadboard.png)` — caption: "Yours looks like this. One difference: the power wire goes to **pin 8** (not 5V) so the Arduino can switch the light on and off."
- **💻 Load the code:** open `sketches/m1_first_light/m1_first_light.ino`, set Board = Arduino Uno and Port (`/dev/ttyUSB0` or `/dev/ttyACM0`), click Upload.
- **✅ It works when…** your LED blinks on/off twice a second.
- **🔧 Not working? Try…** must include:
  - LED not lighting? It only works one way — pull it out, flip it, push it back (long leg toward the resistor/pin 8 side).
  - Check the resistor and wires share the right rows (push them in firmly).
  - Upload error/no port? See Mission 0's troubleshooting.
- **🔬 Now try this:** (1) change both `500`s to `1000` for slow blinking; (2) swap the 220Ω resistor for the 1kΩ, then 10kΩ — the light gets dimmer because a bigger resistor lets less electricity through.
- **💡 What's happening:** pin 8 turns on and off. The resistor protects the LED by limiting the electricity. An LED only lights when its long leg points the right way.
- **👨‍👩‍👧 Grown-up's corner:** any digital pin works; we use 8 to keep pin 13's onboard LED out of the picture. 220Ω is the safe default; the higher values just demonstrate current limiting.

- [ ] **Step 2: Lint the sheet**

Run: `tools/lint_sheet.sh lessons/m1-01-first-light.md "🎯" "🧰" "🔌" "💻" "✅" "🔧" "🔬" "💡"`
Expected: `OK: …`, exit code 0.

- [ ] **Step 3: Commit**

```bash
git add lessons/m1-01-first-light.md
git commit -m "Add Mission 1 First Light sheet"
```

---

### Task 9: Mission 1 Traffic Light sketch

**Files:**
- Create: `sketches/m1_traffic_light/m1_traffic_light.ino`

- [ ] **Step 1: Write the sketch**

Create `sketches/m1_traffic_light/m1_traffic_light.ino`:
```cpp
/*
  Mission 1 Project - Traffic Light
  Three LEDs take turns like a real traffic light:
  green (go), yellow (get ready), red (stop), over and over.
  green  -> pin 8
  yellow -> pin 9
  red    -> pin 10
*/

int greenPin  = 8;
int yellowPin = 9;
int redPin    = 10;

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  // GREEN - go!
  digitalWrite(greenPin, HIGH);
  delay(3000);
  digitalWrite(greenPin, LOW);

  // YELLOW - get ready to stop
  digitalWrite(yellowPin, HIGH);
  delay(1000);
  digitalWrite(yellowPin, LOW);

  // RED - stop!
  digitalWrite(redPin, HIGH);
  delay(3000);
  digitalWrite(redPin, LOW);
}
```

- [ ] **Step 2: Compile to verify**

Run: `arduino-cli compile --fqbn arduino:avr:uno sketches/m1_traffic_light`
Expected: success (exit 0).

- [ ] **Step 3: Commit**

```bash
git add sketches/m1_traffic_light/m1_traffic_light.ino
git commit -m "Add Mission 1 Traffic Light sketch"
```

---

### Task 10: Mission 1 Traffic Light sheet

**Files:**
- Create: `lessons/m1-02-traffic-light.md`

- [ ] **Step 1: Write the sheet**

Create `lessons/m1-02-traffic-light.md` following `_template.md` (ALL build sections). Required content/facts:

- **Title:** `# Mission 1 · Traffic Light`
- **🎯 What you're making:** a real traffic light — green, then yellow, then red, on its own.
- **🧰 Grab these parts:** Arduino Uno ×1; breadboard ×1; 1 green + 1 yellow + 1 red LED; 3 × 220Ω resistors; 4 jumper wires.
- **🔌 Build it:** explain it's the **First Light circuit done three times**, once per LED:
  1. Green LED through a 220Ω resistor to **pin 8**.
  2. Yellow LED through a 220Ω resistor to **pin 9**.
  3. Red LED through a 220Ω resistor to **pin 10**.
  4. Every LED's short (–) leg connects to a **GND** rail, and one wire joins that rail to the Arduino's **GND**.
  - Reuse image: `![one LED — repeat it three times](../images/m1-first-light-breadboard.png)` with caption "Build this three times — one green on pin 8, one yellow on pin 9, one red on pin 10."
- **💻 Load the code:** open `sketches/m1_traffic_light/m1_traffic_light.ino`, set Board/Port, Upload.
- **✅ It works when…** green stays on a few seconds, then yellow blinks on briefly, then red, then it repeats.
- **🔧 Not working? Try…**:
  - Only one or two light up? Check each LED's long leg is on the resistor/pin side and the – leg is on the GND rail.
  - Wrong order? Make sure green=pin 8, yellow=pin 9, red=pin 10.
  - Upload/port trouble? See Mission 0.
- **🔬 Now try this:** make green last longer (change `delay(3000)` under GREEN to `5000`); make yellow quicker (`500`). Bonus challenge: can you make it blink red 3 times at the end?
- **💡 What's happening:** the code lights one pin, waits, turns it off, then the next — so the lights take turns. `delay` sets how long each color stays on.
- **👨‍👩‍👧 Grown-up's corner:** this is the same single-LED circuit repeated on three pins; great moment to point out that "more complex" is often just "simple, repeated."

- [ ] **Step 2: Lint the sheet**

Run: `tools/lint_sheet.sh lessons/m1-02-traffic-light.md "🎯" "🧰" "🔌" "💻" "✅" "🔧" "🔬" "💡"`
Expected: `OK: …`, exit code 0.

- [ ] **Step 3: Commit**

```bash
git add lessons/m1-02-traffic-light.md
git commit -m "Add Mission 1 Traffic Light sheet"
```

---

### Task 11: Mission 1 RGB bonus sketch

**Files:**
- Create: `sketches/m1_rgb_rainbow/m1_rgb_rainbow.ino`

- [ ] **Step 1: Write the sketch** (pins/polarity MATCH the kit: common-cathode, RED=6, GREEN=5, BLUE=3)

Create `sketches/m1_rgb_rainbow/m1_rgb_rainbow.ino`:
```cpp
/*
  Mission 1 Bonus - Rainbow Light
  One LED that can glow ANY color by mixing red, green, and blue light.
  Wiring matches the kit: RED leg -> pin 6, GREEN leg -> pin 5, BLUE leg -> pin 3.
  The longest leg is the "minus" leg and goes to GND.
*/

int redPin   = 6;
int greenPin = 5;
int bluePin  = 3;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

// Mix a color. Each number is 0 (off) to 255 (brightest).
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void loop() {
  setColor(255, 0, 0);     delay(1000);  // red
  setColor(0, 255, 0);     delay(1000);  // green
  setColor(0, 0, 255);     delay(1000);  // blue
  setColor(255, 255, 0);   delay(1000);  // yellow
  setColor(128, 0, 255);   delay(1000);  // purple
  setColor(255, 255, 255); delay(1000);  // white
}
```

- [ ] **Step 2: Compile to verify**

Run: `arduino-cli compile --fqbn arduino:avr:uno sketches/m1_rgb_rainbow`
Expected: success (exit 0).

- [ ] **Step 3: Commit**

```bash
git add sketches/m1_rgb_rainbow/m1_rgb_rainbow.ino
git commit -m "Add Mission 1 RGB rainbow bonus sketch"
```

---

### Task 12: Mission 1 RGB bonus sheet

**Files:**
- Create: `lessons/m1-03-rgb-rainbow.md`

- [ ] **Step 1: Write the sheet**

Create `lessons/m1-03-rgb-rainbow.md` following `_template.md` (ALL build sections). Required content/facts:

- **Title:** `# Mission 1 · Bonus: Rainbow Light`
- **🎯 What you're making:** one LED that can become any color you want.
- **🧰 Grab these parts:** Arduino Uno ×1; breadboard ×1; 1 RGB LED (the clear one with **4 legs**); 3 × 220Ω resistors; 4 jumper wires.
- **🔌 Build it:** the RGB LED has 4 legs. The **longest leg** is the minus (–) leg → goes to **GND**. The other three are red, green, blue light:
  1. Longest leg → **GND**.
  2. Red leg → 220Ω resistor → **pin 6**.
  3. Green leg → 220Ω resistor → **pin 5**.
  4. Blue leg → 220Ω resistor → **pin 3**.
  - Image: `![RGB wiring](../images/m1-rgb-breadboard.png)`.
- **💻 Load the code:** open `sketches/m1_rgb_rainbow/m1_rgb_rainbow.ino`, set Board/Port, Upload.
- **✅ It works when…** the LED slowly cycles red → green → blue → yellow → purple → white and repeats.
- **🔧 Not working? Try…**:
  - Only some colors show? One leg may be in the wrong row — check red=pin 6, green=pin 5, blue=pin 3.
  - No light at all? Make sure the **longest** leg goes to GND.
  - Colors look swapped? Double-check which leg is which (the legs are different lengths next to the longest one).
- **🔬 Now try this:** invent your own color! Add a line like `setColor(255, 100, 0); delay(1000);` for orange. Numbers are 0–255 for how much red, green, blue.
- **💡 What's happening:** `analogWrite` can set a leg anywhere from off (0) to full (255). Mixing red, green, and blue light makes every other color — that's how screens make color too.
- **👨‍👩‍👧 Grown-up's corner:** this LED is common-cathode (shared –), so higher numbers = brighter. `analogWrite` uses PWM on pins 3/5/6.

- [ ] **Step 2: Lint the sheet**

Run: `tools/lint_sheet.sh lessons/m1-03-rgb-rainbow.md "🎯" "🧰" "🔌" "💻" "✅" "🔧" "🔬" "💡"`
Expected: `OK: …`, exit code 0.

- [ ] **Step 3: Commit**

```bash
git add lessons/m1-03-rgb-rainbow.md
git commit -m "Add Mission 1 RGB rainbow bonus sheet"
```

---

### Task 13: Booklet build (Markdown → printable PDF)

**Files:**
- Create: `tools/booklet.css`, `tools/build_booklet.sh`

- [ ] **Step 1: Write the print stylesheet**

Create `tools/booklet.css`:
```css
@page { margin: 1.5cm; }
body {
  font-family: "Trebuchet MS", "Comic Sans MS", Verdana, sans-serif;
  font-size: 13pt;
  line-height: 1.5;
  color: #1a1a1a;
}
h1 {
  page-break-before: always;
  font-size: 24pt;
  color: #c0392b;
  border-bottom: 4px solid #f1c40f;
  padding-bottom: 6px;
}
h1:first-of-type { page-break-before: avoid; }
h2 { font-size: 16pt; color: #2c3e50; margin-top: 1.1em; }
img { max-width: 90%; display: block; margin: 12px auto; border: 2px solid #ddd; border-radius: 6px; }
code, pre { font-family: "DejaVu Sans Mono", monospace; background: #f4f4f4; }
pre { padding: 10px; border-radius: 6px; border: 1px solid #ddd; font-size: 11pt; white-space: pre-wrap; }
blockquote { background: #eaf6ff; border-left: 5px solid #3498db; padding: 8px 12px; border-radius: 4px; }
```

- [ ] **Step 2: Write the build script**

Create `tools/build_booklet.sh`:
```bash
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
  --embed-resources --standalone \
  --pdf-engine=wkhtmltopdf \
  -o build/arduino-missions.pdf
echo "Built build/arduino-missions.pdf"
```

- [ ] **Step 3: Make it executable**

Run: `chmod +x tools/build_booklet.sh`

- [ ] **Step 4: Build the PDF and verify it is non-empty**

Run: `tools/build_booklet.sh && ls -la build/arduino-missions.pdf`
Expected: prints the four sheet paths in order (m0-01, m1-01, m1-02, m1-03) and creates `build/arduino-missions.pdf` with size > 0.
Verify pages render: `pdfinfo build/arduino-missions.pdf | grep Pages` → Pages ≥ 4.

- [ ] **Step 5: Commit**

```bash
git add tools/booklet.css tools/build_booklet.sh
git commit -m "Add booklet build pipeline (md -> printable PDF)"
```

---

### Task 14: README (how to use + how to print)

**Files:**
- Create: `README.md`

- [ ] **Step 1: Write the README**

Create `README.md`:
```markdown
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
```

- [ ] **Step 2: Commit**

```bash
git add README.md
git commit -m "Add README with usage and printing instructions"
```

---

## Self-review notes (author)

- **Spec coverage:** Working-mode (solo/9yo) → reduced-section Mission 0 + checkpoints/troubleshooting in every sheet (Tasks 6, 8, 10, 12). Load-and-tweak → ready-made sketches + `🔬 Now try this` (Tasks 5–12). Printable booklet → Task 13. Mission-based w/ payoff → Mission 1 ends in Traffic Light project (Task 10). Linux → port + dialout notes (Tasks 6, 14). Reuse kit wiring art → Task 4. No Mermaid → none used. Pilot-first (M0+M1 only) → whole plan scoped to that.
- **Placeholder scan:** RGB image page is chosen by visual inspection within a stated range (49–53) with an explicit selection criterion — the only non-deterministic step, and it is a genuine human judgment, not a TODO. All sketches are complete and compile-checked. Sheet tasks specify exact facts (pins, parts, checkpoints, tweaks, troubleshooting); sentence-level prose is drafted during implementation against the voice guide and enforced by lint.
- **Consistency:** Pins are consistent across sketches and sheets — First Light pin 8; Traffic Light green=8/yellow=9/red=10; RGB red=6/green=5/blue=3 (matches kit). Sketch folder names match `.ino` names (arduino-cli requirement). Section markers identical in template, lint calls, and sheets.
```
