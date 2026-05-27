# Mission 1 · Traffic Light

## 🎯 What you're making

A real traffic light — green, then yellow, then red — switching on its own, over and over.

## 🧰 Grab these parts

- [ ] Arduino Uno × 1
- [ ] Breadboard × 1
- [ ] Green LED × 1
- [ ] Yellow LED × 1
- [ ] Red LED × 1
- [ ] 220Ω resistors × 3 (stripes: red, red, brown)
- [ ] Jumper wires × 4

## 🔌 Build it

This is the First Light circuit done three times — once per LED. Each LED gets its own resistor and its own pin.

1. **Green LED:** long (+) leg → 220Ω resistor → **pin 8**. Short (–) leg → GND rail.
2. **Yellow LED:** long (+) leg → 220Ω resistor → **pin 9**. Short (–) leg → GND rail.
3. **Red LED:** long (+) leg → 220Ω resistor → **pin 10**. Short (–) leg → GND rail.
4. Run **one wire from the GND rail** to a **GND pin** on the Arduino. All three LEDs share that one GND wire.

![one LED — repeat it three times](../images/m1-first-light-breadboard.png)

*Build this three times — one green LED on pin 8, one yellow on pin 9, one red on pin 10. All three short legs share the GND rail.*

## 💻 Load the code

1. Open **`sketches/m1_traffic_light/m1_traffic_light.ino`** in the Arduino software.
2. Set **Tools → Board → Arduino Uno**.
3. Set **Tools → Port** → `/dev/ttyUSB0` or `/dev/ttyACM0`.
4. Click **Upload**.

## ✅ It works when…

Green lights up for a few seconds. Then it turns off and yellow comes on briefly. Then red stays on for a few seconds. Then it starts over from green — all on its own.

## 🔧 Not working? Try…

- **Only one or two lights work?** Check each LED one at a time. The long leg should be on the resistor/pin side. The short leg should be on the GND rail.
- **Lights come on in the wrong order?** Double-check the pins: green = pin 8, yellow = pin 9, red = pin 10.
- **Upload trouble?** See Mission 0's troubleshooting for the port and permission fixes.

## 🔬 Now try this

- Make green last longer: find `delay(3000)` under the `// GREEN` comment and change it to `5000`. Upload. Now green stays on 5 full seconds — more like a real light.
- Make yellow quicker: change its `delay(1000)` to `500`. Yellow should feel like a warning now.
- **Bonus challenge:** can you make red blink three times before turning off? Hint: turn the red light on, wait a little, turn it off, wait a little — then do that three times in a row.

## 💡 What's happening

The code turns one pin on, waits, turns it off, then moves to the next pin. Green, then yellow, then red — and `loop()` starts the whole thing again. The `delay()` numbers control how long each color stays on. More time = bigger number.

## 👨‍👩‍👧 Grown-up's corner

This is the same single-LED circuit from First Light, just repeated on three pins. It's a great moment to point out that "more complex" is often just "simple, repeated." The timing values (3000 / 1000 / 3000 ms) loosely mirror real traffic-light ratios — green and red are equal; yellow is short. The bonus blink challenge is an informal intro to loops-within-loops.
