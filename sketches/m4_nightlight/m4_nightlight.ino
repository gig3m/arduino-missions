// m4_nightlight.ino — Mission 4 · Nightlight
// A photocell (LDR) senses how bright or dark the room is.
// The LED gets BRIGHTER when the room gets DARKER — just like a real nightlight!
//
// Wiring:
//   LDR one leg → 5V
//   LDR other leg → A0   AND through a 10kΩ resistor → GND
//   LED (+) → 220Ω resistor → pin 9 (~)
//   LED (–) → GND

const int ldrPin = A0;  // photocell voltage divider
const int ledPin = 9;   // PWM pin — look for the ~ symbol on your board

void setup() {
  // A0 is analog input by default — no pinMode needed
  // pin 9 is output for the LED
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int light = analogRead(ldrPin); // 0 (dark) to 1023 (bright)

  // Invert and map: dark room → high light reading → bright LED
  // When light is 0 (dark), brightness = 255 (full bright).
  // When light is 1023 (bright), brightness = 0 (LED off).
  int brightness = map(light, 0, 1023, 255, 0);

  analogWrite(ledPin, brightness); // 0–255 controls LED brightness

  delay(50); // small pause so the reading is steady
}
