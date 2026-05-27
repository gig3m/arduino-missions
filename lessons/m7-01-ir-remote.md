# Mission 7 · IR Remote Reader

## 🧩 First, install a library

The IR receiver needs a helper library to decode the remote's signals. Do this before wiring anything:

1. Open the Arduino software.
2. Go to **Tools → Manage Libraries…**
3. In the search box, type **IRremote** and press Enter.
4. Find **IRremote** by *Arduino-IRremote* in the list and click **Install**.
5. If it asks about dependencies, click **Install All**.
6. Close the library manager when it's done.

## 🎯 What you're making

You're going to spy on your remote control! Every button you press sends an invisible infrared beam. Your Arduino will catch that beam and decode it. The Serial Monitor will show you the secret code for every button.

## 🧰 Grab these parts

- [ ] Arduino Uno × 1
- [ ] IR receiver module × 1 (small black sensor on a tiny board — it has three pins)
- [ ] Jumper wires × 3 (male-to-male)
- [ ] Kit remote control × 1

## 🔌 Build it

The IR receiver module has three pins. Look at the labels on the back of the board: **GND**, **VCC**, and **DATA** (sometimes written **S** or **OUT**).

1. Run a wire from the **GND pin** to a **GND pin** on the Arduino.
2. Run a wire from the **VCC pin** to the **5V pin** on the Arduino.
3. Run a wire from the **DATA pin** to **pin 11** on the Arduino.

The sensor's round black eye should point away from the board — toward where you'll point the remote.

![IR receiver wiring](../images/m7-ir-remote-breadboard.png)

## 💻 Load the code

1. Open **`sketches/m7_ir_remote/m7_ir_remote.ino`** in the Arduino software.
2. Set **Tools → Board → Arduino Uno**.
3. Set **Tools → Port** → pick `/dev/ttyUSB0` or `/dev/ttyACM0`.
4. Click **Upload**. Wait for "Done uploading."
5. Go to **Tools → Serial Monitor**. Set the speed to **9600 baud** (bottom-right dropdown).

## ✅ It works when…

Point the remote straight at the black sensor eye from about 30 cm (a ruler's length) away. Press any button. The Serial Monitor shows a line like this:

```
Button code: 0xF30CFF00
```

Every button shows a different code. Try pressing the same button twice — you'll get the same code both times!

## 🔧 Not working? Try…

- **No codes showing up?** Aim the remote straight at the sensor's round black eye. Aim it from about 30 cm away. Check the battery in the remote — put in a fresh one if the light isn't blinking.
- **Library error when uploading?** Make sure you installed **IRremote** in Manage Libraries. Close and reopen the Arduino software after installing.
- **Wrong baud rate?** The Serial Monitor dropdown at the bottom-right must say **9600 baud**. Change it if it says something else.
- **Upload error?** See Mission 0's troubleshooting for the port and permission fix.

## 🔬 Now try this

- Press **every button** on the remote and write down the code each one shows. That list is YOUR remote's code map — you'll need it in the next build!
- Press the same button many times quickly. The words **REPEAT** might appear — that's the remote saying "same button again."
- Find the line `Serial.print("Button code: 0x");` in the sketch. Change the label text to anything you like — `"Secret signal: 0x"` — upload again and see your label in the monitor.

## 💡 What's happening

Your remote control has a tiny LED inside that flashes infrared light really fast — so fast your eyes can't see it. The IR receiver picks up those flashes and turns them into a number. That number is different for every button. It's like each button has its own secret knock. The Arduino reads the knock and prints the code. In the next build, you'll use that code to make something actually happen!

## 👨‍👩‍👧 Grown-up's corner

This build uses the **IRremote v4.x** library (install via Library Manager; the sketch uses the v4 API: `IrReceiver.begin()`, `IrReceiver.decode()`, `IrReceiver.decodedIRData.decodedRawData`, `IrReceiver.resume()`). The kit's bundled sketch uses the older v2 API (`irrecv.enableIRIn()`, `irrecv.decode()`) — do not use that; it won't compile with v4. The kit remote uses NEC protocol. `ENABLE_LED_FEEDBACK` blinks the pin 13 LED on each received frame — useful for confirming reception. The built-in LED feedback shares pin 13 but only reads, doesn't conflict.
