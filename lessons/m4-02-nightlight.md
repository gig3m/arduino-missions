# Mission 4 · Nightlight

## 🎯 What you're making

A real nightlight. When the room is bright, the LED stays off. When you cover the sensor with your hand — or turn off the lights — the LED gets brighter all by itself. No switch needed. It just knows.

## 🧰 Grab these parts

- [ ] Arduino Uno × 1
- [ ] Breadboard × 1
- [ ] Photocell (LDR) × 1 (looks like a tiny orange disc with a squiggly symbol on top — two legs)
- [ ] 10kΩ resistor × 1 (stripes: brown, black, orange)
- [ ] LED × 1 (any color)
- [ ] 220Ω resistor × 1 (stripes: red, red, brown)
- [ ] Jumper wires × 5 (male-to-male)

## 🔌 Build it

This build has two parts: the **light sensor** (photocell + resistor) and the **LED**.

**Light sensor (voltage divider):**

The photocell is a resistor that changes — brighter light means less resistance. You pair it with a fixed 10kΩ resistor so the Arduino can measure the difference.

1. Push the photocell into the breadboard. The two legs go in **two different rows**. (It has no + or –  — either direction is fine.) Let's call them **row A** and **row B**.
2. Run a wire from **row A** to the **5V pin** on the Arduino. This is the "top" of the sensor.
3. Push the **10kΩ resistor** so one end is in **row B** and the other end is in a **new empty row** (call it **row C**).
4. Run a wire from **row C** to a **GND pin** on the Arduino. This is the "bottom" of the sensor.
5. Run a wire from **row B** to **pin A0** on the Arduino. (A0 is in the "Analog In" group on the left side of the board.) **Important:** A0 goes to **row B** — the spot where the photocell meets the 10kΩ resistor — **not** to row A with the 5V wire.

So the chain is: **5V → photocell → row B → 10kΩ → GND**, and **A0 taps row B** — the spot in the middle. That middle tap is the key: it's the only spot whose voltage changes as the light changes.

**LED:**

6. Push the **LED** a few rows away from the sensor. Long (+) leg in one row, short (–) leg in the next row.
7. Push the **220Ω resistor** so one end is in the **same row as the LED's long (+) leg** and the other end is in a free row.
8. Run a wire from **pin 9** on the Arduino to that free row (the far end of the 220Ω resistor). *Look for the ~ next to pin 9 — that tilde means it can do PWM dimming.*
9. Run a wire from the **LED's short (–) leg row** to a **GND pin** on the Arduino.

> **No wiring image for this one** — this is a custom combo, so the steps above are your guide. Trace each wire with your finger before uploading.

## 💻 Load the code

1. Open **`sketches/m4_nightlight/m4_nightlight.ino`** in the Arduino software.
2. Set **Tools → Board → Arduino Uno**.
3. Set **Tools → Port** → pick `/dev/ttyUSB0` or `/dev/ttyACM0`.
4. Click **Upload**. Wait for "Done uploading."

## ✅ It works when…

You cover the photocell with your hand and the LED **slowly gets brighter**. Remove your hand and it **slowly fades back down**. In a dark room, the LED glows at full brightness on its own.

## 🔧 Not working? Try…

- **LED is always full bright no matter what?** Check that the A0 wire connects to the junction between the photocell and the 10kΩ resistor — not to the 5V side or the GND side. That middle point is what the Arduino reads.
- **LED is always off?** Make sure pin 9's wire goes to the 220Ω resistor, not directly to the LED's leg. Also check the LED is the right way around (long leg toward the resistor).
- **Sensor not responding?** Press every wire firmly into the breadboard — loose holes are sneaky. Check both photocell legs are in different rows (not the same row, which would short them).
- **Upload error?** See Mission 0's troubleshooting for the port and permission fix.

## 🔬 Now try this

- Cover the photocell slowly with your hand. Watch how the LED fades up gradually — not just on or off. That smooth change is **analog** at work: 1,024 different light levels, 256 different brightness levels.
- In the code, find `map(light, 0, 1023, 255, 0)`. Change the last two numbers to `0, 255` instead. Upload. Now the LED is a **daylight detector** — brighter room means brighter LED. Which way is more useful as a nightlight?
- Add a line right before `analogWrite`: `Serial.println(light);` and add `Serial.begin(9600);` in `setup()`. Upload and open the Serial Monitor (**Tools → Serial Monitor**, also see Mission 0). Watch the numbers change as you cover and uncover the sensor.

## 💡 What's happening

The photocell and the 10kΩ resistor form a **voltage divider**. When the room is bright, the photocell has low resistance, so most of the 5V drops across the fixed resistor — A0 reads a high number. When the room is dark, the photocell has high resistance, so now most of the 5V drops across the photocell — A0 reads a low number. The code inverts that: low number → full brightness. Pin 9's tilde (~) lets it fake a dimmer with very fast pulses (PWM) — too fast to see, but your eye sees it as brightness.

## 👨‍👩‍👧 Grown-up's corner

The voltage divider formula is Vout = 5V × R_fixed / (R_LDR + R_fixed). 10kΩ is chosen to match the LDR's mid-range resistance in typical indoor lighting, centering the A0 reading around 512. `map()` does a linear interpolation from [0, 1023] to [255, 0] — inverting the relationship so dark = bright LED. `analogWrite` outputs 490 Hz PWM on pin 9 (Timer 1). The 50 ms delay prevents jitter from very fast reads. Kit reference: the LDR from Lesson 18, but without the 74HC595 — simpler and more appropriate for this mission's focus.
