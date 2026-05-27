# Mission 2 · Knob Dimmer

## 🎯 What you're making

A dimmer switch — just like the ones on a wall. Turn a knob all the way left and the LED goes dark. Turn it all the way right and the LED blazes bright. Anywhere in between and it's somewhere in the middle. You control the brightness with your fingers.

## 🧰 Grab these parts

- [ ] Arduino Uno × 1
- [ ] Breadboard × 1
- [ ] Potentiometer × 1 (the blue dial-shaped part with three legs — "pot" for short)
- [ ] LED × 1 (any color — long leg and short leg)
- [ ] 220Ω resistor × 1 (stripes: red, red, brown)
- [ ] Jumper wires × 5 (male-to-male)

## 🔌 Build it

The potentiometer has **three legs** in a row. The two **outer legs** get power. The **middle leg** (called the wiper) carries a signal that changes as you turn the knob.

1. Push the potentiometer into the breadboard. All three legs should be in **three different rows**.
2. Run a wire from the **left outer leg** to the **5V pin** on the Arduino.
3. Run a wire from the **right outer leg** to a **GND pin** on the Arduino.
4. Run a wire from the **middle leg** (wiper) to **pin A0** on the Arduino. (A0 is in the "Analog In" group on the left side of the board.)
5. Place the **LED** a few rows away. Long (+) leg in one row, short (–) leg in the next row.
6. Push the **220Ω resistor** between the **long (+) leg's row** and a free row.
7. Run a wire from **pin 6** on the Arduino to that free row (the far end of the resistor). *Look for the \~ symbol next to pin 6 — that tilde means it can do PWM.*
8. Run a wire from the **short (–) leg's row** to **GND**.

> **No wiring image for this one** — the pot+LED combo doesn't appear in the kit diagrams, so the word steps above are your guide. If you get stuck, re-read each step slowly and trace each wire with your finger before moving on.

## 💻 Load the code

1. Open **`sketches/m2_dimmer/m2_dimmer.ino`** in the Arduino software.
2. Set **Tools → Board → Arduino Uno**.
3. Set **Tools → Port** → pick `/dev/ttyUSB0` or `/dev/ttyACM0`.
4. Click **Upload**. Wait for "Done uploading."

## ✅ It works when…

You turn the potentiometer knob slowly from one end to the other and the LED **smoothly changes brightness** — from nearly off at one end to full bright at the other.

## 🔧 Not working? Try…

- **LED is always off?** Flip the LED around — long leg toward the resistor (pin 6 side). Make sure the wire from pin 6 goes to the resistor, not directly to the LED.
- **LED is always full bright no matter which way you turn the knob?** Check that the wiper (middle leg) is connected to A0, not to 5V. Double-check which leg is which — look straight down at the pot; the middle leg is the wiper.
- **LED flickers wildly?** A loose wire on the pot legs is the usual cause. Press each jumper wire firmly into its hole.
- **Upload error?** See Mission 0's troubleshooting for the port and permission fix.

## 🔬 Now try this

- Turn the knob slowly all the way from one side to the other. Watch how smooth the change is. That smoothness is **analog** — 1,024 different levels, not just on/off.
- In the code, find `analogRead(potPin) / 4`. Change the `4` to `8`. Upload and turn the knob. The LED reaches full bright at only **halfway** — after that it stays at max. Why? (Hint: 1023 ÷ 8 = 127, which is less than 255.)
- Change `ledPin = 6` to `ledPin = 5`. Wire a second LED with its own 220Ω resistor to **pin 5**. Now **both** LEDs dim and brighten together with one knob.

## 💡 What's happening

The potentiometer is a variable resistor. As you turn the knob, the resistance on the wiper leg changes. The Arduino reads that as a number from **0 to 1,023** on pin A0. But `analogWrite` only understands **0 to 255**. Dividing by 4 squishes the range to fit. Pin 6's tilde (~) means it can "fake" a dimmer voltage using very fast on-off pulses — too fast for your eyes to see the flicker. Your brain sees it as brightness. That trick is called PWM (pulse-width modulation).

## 👨‍👩‍👧 Grown-up's corner

`analogRead` returns a 10-bit value (0–1023); `analogWrite` takes an 8-bit value (0–255). Integer division by 4 maps the ranges without floating-point overhead — deliberate for the Uno's limited resources. The ~ pins (3, 5, 6, 9, 10, 11 on the Uno) output 490 Hz or 980 Hz PWM depending on the timer. The `loop()` runs thousands of times per second, so the pot read → brightness write is effectively continuous. The "divide by 8" explore is a gentle intro to range mapping and saturation — the concept that scaling affects both the ceiling and the granularity.
