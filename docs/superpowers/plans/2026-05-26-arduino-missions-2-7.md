# Arduino Missions 2–7 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development to implement this plan task-by-task (one implementer subagent per mission + review). Steps use checkbox (`- [ ]`) syntax.

**Goal:** Build the remaining missions (2–7) of the Arduino Missions booklet, following the exact pattern, template, and conventions established by the Mission 0/1 pilot and `CLAUDE.md`.

**Architecture:** Per mission: a few component "skill" sheets + a combine-the-parts project sheet, each backed by a tidy, compile-verified `.ino` (derived from the kit's bundled example for correct pins) and a kit-extracted wiring image. Same `lessons/` + `sketches/` + `images/` layout. Booklet builds via pandoc + headless Chrome.

**Tech Stack:** Markdown, Arduino C++ (AVR/Uno), arduino-cli (+ libraries as noted), pandoc, headless Chrome, pdftoppm, ImageMagick.

**Read first:** `CLAUDE.md` (conventions, voice, lint/compile/build commands) and `lessons/_template.md`. Existing pilot sheets in `lessons/m0-*`, `m1-*` are the reference for tone and structure.

**Source of truth for pins:** the kit's bundled sketches at
`~/Downloads/elegoo_code/ELEGOO Super Starter Kit for UNO V1.0.2023.05.05/Deutsch/code/<Lesson …>/…/*.ino`.
Each sketch below is derived from the named kit `.ino` (clean it up for a kid; keep the pins) and MUST compile (`arduino-cli compile --fqbn arduino:avr:uno sketches/<dir>`) before commit.

**Kit PDF (for wiring images):**
`~/Downloads/elegoo_extract/ELEGOO Super Starter Kit for UNO V1.0.2023.05.05/English/Elegoo Super Starter Kit for UNO V1.0.2019.09.17.pdf`
Extract a lesson's breadboard render: `pdftoppm -png -r 200 -f <a> -l <b> "<pdf>" build/p`, view the pages, pick the **colorful breadboard wiring diagram**, then `magick build/p-<n>.png -trim +repage images/<name>.png`.

**Conventions carried from the pilot (apply to every sheet):**
- 9-year-old voice; build sheets use all 8 markers (`🎯 🧰 🔌 💻 ✅ 🔧 🔬 💡`) + optional `👨‍👩‍👧`; lint before commit.
- Reuse the kit's wiring image when the build matches a kit lesson 1:1. For **novel/combined** builds (no exact kit image), rely on explicit literal word-steps and embed the closest component image with an honest caption (e.g., "yours adds a buzzer on pin 12"). This is the deliberate pilot approach; if the child struggles with it, the fallback is custom Fritzing diagrams (deferred).
- Troubleshooting references Mission 0 for port/`dialout` issues.
- `🔬 Now try this` gives exact values to change.
- Prefer **no-library** sketches. Where a library is unavoidable (DHT11, IR), add a `🧩 First, install a library` step (Arduino IDE → Tools → Manage Libraries → search/install) and a grown-up note; mark the build a **bonus**.

**Naming:** sheets `m<N>-<NN>-<slug>.md`; sketches `sketches/m<N>_<slug>/m<N>_<slug>.ino`.

---

### Task A: Mission 2 — You're in Control (button + potentiometer)

**Builds / sheets:**
- `m2-01-button-switch.md` + `sketches/m2_button/m2_button.ino`
- `m2-02-knob-dimmer.md` + `sketches/m2_dimmer/m2_dimmer.ino` (project)

**Facts (from kit Lesson 5 `Digital Inputs`):** two push buttons → **pin 9** and **pin 8** (use `INPUT_PULLUP`, pressed = LOW), LED → **pin 5**. Core only.
- **Button sketch:** one button (pin 9) turns the LED (pin 5) ON, the other (pin 8) turns it OFF. Match kit pins so the kit image applies. Image: extract from kit Lesson 5 (pages ~55–59), the breadboard render with 2 buttons + LED.
- **Knob dimmer (project):** potentiometer outer legs → **5V** and **GND**, middle (wiper) leg → **A0**; LED + 220Ω → **pin 6** (PWM). Sketch: `analogWrite(6, analogRead(A0) / 4);` in loop (1023→255). Core only. **No exact kit image** → literal word-steps (pot has 3 legs); optionally reuse the button image is NOT appropriate — describe in words. `🔬`: turn the knob, watch brightness; change pin 6 to drive two LEDs.

**Verify:** compile both sketches; lint both sheets with the 8 markers. **Commit** each sheet and sketch (clear messages, e.g., "Add Mission 2 button switch sketch/sheet").

---

### Task B: Mission 3 — Make Some Noise (active + passive buzzer)

**Builds / sheets:**
- `m3-01-beep.md` + `sketches/m3_beep/m3_beep.ino` (active buzzer)
- `m3-02-mini-piano.md` + `sketches/m3_mini_piano/m3_mini_piano.ino` (project, passive buzzer + buttons)

**Facts:**
- Active buzzer (kit Lesson 6): buzzer → **pin 12**, just `digitalWrite(12, HIGH/LOW)` with delays (active buzzer makes its own tone). Core. Image: kit Lesson 6 (pages ~60–63).
- Passive buzzer (kit Lesson 7): buzzer → **pin 8**, uses `tone(8, frequency, duration)`. Core (`tone()` is built-in). **Do NOT depend on `pitches.h`** — define the few note frequencies inline as `int` constants (e.g., C4=262, D4=294, E4=330, …) so the sketch is self-contained.
- **Mini-piano project:** reuse the buttons from Mission 2 (pins 9, 8 with `INPUT_PULLUP`) so each button plays a different note on the passive buzzer (pin 8 conflicts with a button — use buzzer on **pin 12** for the piano to avoid the pin-8 button clash, and buttons on 9 and 8). Each pressed button → `tone(12, noteFreq)`; released → `noTone(12)`. Core. Image: combine — use the passive-buzzer kit image with an honest caption (adds buttons). Literal word-steps for the buttons.
- `🔬`: change the note frequencies; add a third note if a third button is available; make `tone` durations into a short melody.

**Verify/commit:** compile both; lint both; commit each.

---

### Task C: Mission 4 — Sensing the World (tilt, light, distance; DHT11 bonus)

**Builds / sheets:**
- `m4-01-tilt-switch.md` + `sketches/m4_tilt/m4_tilt.ino`
- `m4-02-nightlight.md` + `sketches/m4_nightlight/m4_nightlight.ino` (project)
- `m4-03-distance-alarm.md` + `sketches/m4_distance_alarm/m4_distance_alarm.ino` (project)
- `m4-04-dht11-weather.md` + `sketches/m4_dht11/m4_dht11.ino` (**bonus**, needs a library)

**Facts:**
- Tilt/ball switch (kit Lesson 8): switch → **pin 2** (enable pull-up: `pinMode(2, INPUT_PULLUP)`), LED → **pin 13** (built-in). Inverted logic (tilt one way = LOW). Core. Image: kit Lesson 8 (pages ~68–71). Build: tilt the breadboard, the LED reacts.
- Nightlight (project): photocell (LDR) in a voltage divider — one LDR leg → **5V**, other leg → **A0** and through a 10kΩ resistor → **GND**; LED + 220Ω → **pin 9** (PWM). Sketch: read `analogRead(A0)`, `analogWrite(9, …)` so the LED gets **brighter as it gets darker** (invert + map). Core, no library. (Kit Lesson 18 uses a 74HC595 — do NOT; this simpler divider is the standard nightlight.) **No exact kit image** → literal word-steps. `🔬`: cover the sensor with your hand; flip the brightness so it's a daylight detector instead.
- Distance alarm (project): HC-SR04 **trig → pin 12, echo → pin 11**; buzzer (active) → **pin 8** (or reuse pin 12? no — trig uses 12; use buzzer on **pin 8**); LED optional. Write the ultrasonic **library-free**: pulse trig HIGH 10µs, `duration = pulseIn(echoPin, HIGH)`, `cm = duration / 58`. If `cm < 15`, beep. Core, no library. Image: kit Lesson 10 (pages ~76–80) breadboard render. `🔬`: change the alarm distance (15) to make it more/less sensitive; print `cm` to the Serial Monitor (tie back to Mission 0).
- **DHT11 weather (bonus):** DHT11 data → **pin 2**. Needs a library. Use the **"DHT sensor library" by Adafruit** (+ "Adafruit Unified Sensor" dependency) via Library Manager, OR the simpler **"SimpleDHT"**. Pick ONE, write the sketch to its API, and add a `🧩 First, install a library` step naming the exact Library Manager search term + a `👨‍👩‍👧` note. Read temp + humidity, print to Serial Monitor. Compile with that library installed (`arduino-cli lib install "<exact name>"`). Image: kit Lesson 11 (pages ~81–86).

**Verify/commit:** compile all (install the DHT library first for the bonus); lint all; commit each.

---

### Task D: Mission 5 — Words & Numbers on Screen (LCD + thermometer; 7-seg & 74HC595 bonus)

**Builds / sheets:**
- `m5-01-hello-screen.md` + `sketches/m5_hello/m5_hello.ino`
- `m5-02-weather-station.md` + `sketches/m5_weather/m5_weather.ino` (project)
- `m5-03-seven-segment.md` + `sketches/m5_seven_seg/m5_seven_seg.ino` (**bonus**)
- `m5-04-led-bar.md` + `sketches/m5_led_bar/m5_led_bar.ino` (**bonus**, 74HC595)

**Facts:**
- LCD1602 (kit Lesson 14, `LiquidCrystal` **built-in**): RS→**7**, E→**8**, D4→**9**, D5→**10**, D6→**11**, D7→**12**; `LiquidCrystal lcd(7,8,9,10,11,12); lcd.begin(16,2); lcd.print("…")`. Build: show his name / "Hello!". Image: kit Lesson 14 (pages ~98–102). Note: the LCD has a contrast pot/backlight — follow the kit wiring exactly.
- Weather station (project): thermistor → **A0** (kit Lesson 15), LCD pins as above. Read `analogRead(A0)`, convert to °C (Steinhart-Hart as in kit, or a simpler approximation — keep it accurate enough), `lcd.print(tempC)`. **No sensor library** (thermistor is analog; LiquidCrystal is built-in). Image: kit Lesson 15 (pages ~103–107). `🔬`: show °F too; update once per second.
- Seven-segment (bonus, kit Lesson 19): single common-cathode 7-seg via 74HC595 — DS→**2**, SH_CP→**4**, ST_CP→**3**; `shiftOut()` digit patterns 0–9. Core. Image: kit Lesson 19 (pages ~126–131).
- LED bar (bonus, kit Lesson 16): 8 LEDs via 74HC595 — DS→**12**, SH_CP→**9**, ST_CP→**11**; `shiftOut(dataPin, clockPin, LSBFIRST, value)`. Core. Image: kit Lesson 16 (pages ~108–114).

**Verify/commit:** compile all; lint all; commit each.

---

### Task E: Mission 6 — Things That Move (servo, DC motor + fan, relay)

**Builds / sheets:**
- `m6-01-servo-wave.md` + `sketches/m6_servo/m6_servo.ino`
- `m6-02-button-fan.md` + `sketches/m6_button_fan/m6_button_fan.ino` (project, DC motor + L293D + button)
- `m6-03-relay-click.md` + `sketches/m6_relay/m6_relay.ino`

**Facts:**
- Servo (kit Lesson 9, `Servo` **built-in**): signal → **pin 9**; `myservo.attach(9); myservo.write(angle);` sweep 0–180. Image: kit Lesson 9 (pages ~72–75). `🔬`: change the sweep range/speed; make it wave.
- DC motor + L293D (kit Lesson 21): ENABLE(PWM)→**5**, IN_A→**3**, IN_B→**4**; direction via the two digital pins, speed via `analogWrite(5, 0–255)`. Core. Attach the fan blade. **Button-fan project:** add a button (pin 2, `INPUT_PULLUP`) that toggles the fan on/off. Image: kit Lesson 21 (pages ~136–145) + word-steps for the button. `🔬`: change fan speed; reverse direction.
- Relay (kit Lesson 22): control pin → **pin 3** (or per kit) driving the relay coil; `digitalWrite` to click it on/off. Core. Image: kit Lesson 22 (pages ~146–150). Emphasize the satisfying CLICK; `👨‍👩‍👧` note on what a relay safely switches (do not wire mains).

**Verify/commit:** compile all; lint all; commit each.

---

### Task F: Mission 7 — Remote Control (IR remote, joystick; stepper bonus)

**Builds / sheets:**
- `m7-01-ir-remote.md` + `sketches/m7_ir_remote/m7_ir_remote.ino` (needs IR library)
- `m7-02-joystick.md` + `sketches/m7_joystick/m7_joystick.ino`
- `m7-03-remote-light.md` + `sketches/m7_remote_light/m7_remote_light.ino` (project, IR + LED)
- `m7-04-stepper.md` + `sketches/m7_stepper/m7_stepper.ino` (**bonus**)

**Facts:**
- IR receiver (kit Lesson 13): signal → **pin 11**. **Needs the IRremote library.** Use the current **IRremote (v4.x)** from Library Manager (`arduino-cli lib install "IRremote"`); write to its current API (`IrReceiver.begin(11, ENABLE_LED_FEEDBACK); IrReceiver.decode(); … IrReceiver.decodedIRData.decodedRawData; IrReceiver.resume();`). Add a `🧩 First, install a library` step. Build: press remote buttons, see codes in the Serial Monitor. Image: kit Lesson 13 (pages ~92–97).
- Joystick (kit Lesson 12): X→**A0**, Y→**A1**, button→**pin 2**. Core. Print X/Y/button to Serial Monitor. Image: kit Lesson 12 (pages ~87–91). `🔬`: light an LED when pushed in a direction.
- Remote-light (project): IR receiver (pin 11) + LED (pin 6); map two remote buttons to LED on/off (read the codes from the IR build's Serial output and put them in the sketch as constants). Needs IRremote. Reuse the IR image + word-steps for the LED. `👨‍👩‍👧` note: how to find the button codes.
- Stepper (bonus, kit Lesson 23, `Stepper` **built-in**): ULN2003 → pins **8, 10, 9, 11** (constructor order `Stepper(2048, 8, 10, 9, 11)`); `setSpeed(rpm); step(±2048)`. Image: kit Lesson 23 (pages ~151–158).

**Verify/commit:** compile all (install IRremote first); lint all; commit each.

---

### Task G: Rebuild booklet + update status

- [ ] **Step 1: Rebuild the full booklet**

Run: `tools/build_booklet.sh`
Expected: builds `build/arduino-missions.pdf` from ALL `lessons/m*-*.md` in order via Chrome; succeeds.
Verify: `pdfinfo build/arduino-missions.pdf | grep Pages` (page count grows to cover all missions).

- [ ] **Step 2: Spot-check render**

Render 3–4 sample pages across the new missions to PNG (`pdftoppm -png -r 90 …`) and confirm: emoji render (color), wiring images appear, page breaks per mission. Fix any sheet that renders wrong.

- [ ] **Step 3: Update status lines**

In `README.md` and `CLAUDE.md`, change the Status line to: all 8 missions (0–7) complete. Commit: "Mark all missions complete".

---

## Self-review notes (author)

- **Spec coverage:** Missions 2–7 from the design spec are each a task (A–F); the design's project payoffs (dimmer, mini-piano, nightlight, distance alarm, weather station, button-fan, remote-light) are all present; abstract kit lessons (74HC595 7-seg/bar, stepper) are bonus builds, as the spec requires. Serial Monitor reused in M4/M7. Task G assembles + updates status.
- **Library discipline:** only DHT11 (M4 bonus) and IR (M7) require an install; both get an explicit in-sheet install step. Ultrasonic and temperature are deliberately library-free.
- **Pin consistency:** pins are taken from the named kit `.ino` files (verified) and noted per build; compile-verification is the gate. Where a project reuses a pin that conflicts (e.g., passive buzzer pin 8 vs button pin 8), the plan resolves it (piano buzzer on pin 12).
- **Known soft spot (deliberate):** novel/combined builds (dimmer, nightlight, button-fan, mini-piano, remote-light) lack an exact kit image and lean on word-steps + closest component image. This is the open question the pilot was meant to test; flagged for the human to watch.
