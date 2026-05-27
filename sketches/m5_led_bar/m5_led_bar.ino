// Mission 5 · LED Bar (bonus)
// Eight LEDs controlled by a 74HC595 shift register.
// LEDs light up one at a time from left to right, like a running light.
//
// Wiring:
//   74HC595 DS   (pin 14) → Arduino pin 12
//   74HC595 ST_CP (pin 12) → Arduino pin 11  (latch)
//   74HC595 SH_CP (pin 11) → Arduino pin 9   (clock)
//   74HC595 VCC  (pin 16) → 5V
//   74HC595 GND  (pin 8)  → GND
//   74HC595 OE   (pin 13) → GND  (always enabled)
//   74HC595 MR   (pin 10) → 5V  (never reset)
//   74HC595 Q0–Q7 → 220Ω resistors → LED anodes (+, long leg)
//   All LED cathodes (–, short leg) → GND

const int dataPin  = 12;  // DS
const int latchPin = 11;  // ST_CP
const int clockPin = 9;   // SH_CP

// Send one byte to the shift register and latch it
void updateLEDs(byte value) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, value);
  digitalWrite(latchPin, HIGH);
}

void setup() {
  pinMode(dataPin,  OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // Start with all LEDs off
  updateLEDs(0);
}

void loop() {
  // Light each LED one at a time, left to right
  for (int i = 0; i < 8; i++) {
    updateLEDs(1 << i);   // shift a 1 bit across positions 0–7
    delay(100);
  }

  // Then fill them up all at once and pause
  updateLEDs(B11111111);
  delay(500);

  // Turn them all off and pause
  updateLEDs(0);
  delay(300);
}
