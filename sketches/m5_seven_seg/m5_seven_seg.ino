// Mission 5 · Seven-Segment Display (bonus)
// Counts down 9 to 0 on a 7-segment display using the 74HC595 shift register.
//
// Wiring:
//   74HC595 DS   (pin 14) → Arduino pin 2
//   74HC595 ST_CP (pin 12) → Arduino pin 3  (latch)
//   74HC595 SH_CP (pin 11) → Arduino pin 4  (clock)
//   74HC595 VCC  (pin 16) → 5V
//   74HC595 GND  (pin 8)  → GND
//   74HC595 OE   (pin 13) → GND  (always enabled)
//   74HC595 MR   (pin 10) → 5V  (never reset)
//   74HC595 Q0–Q7 → 220Ω resistors → 7-segment pins a–g (+ dp)
//   7-segment common cathode legs (pins 3, 8) → GND

// 74HC595 control pins
const int dataPin  = 2;   // DS
const int latchPin = 3;   // ST_CP
const int clockPin = 4;   // SH_CP

// Digit patterns for a common-cathode 7-segment display.
// Bit order: dp-g-f-e-d-c-b-a (Q7 → Q0 from the shift register)
// 1 = segment ON, 0 = segment OFF
//                          dp  g  f  e  d  c  b  a
const byte DIGITS[10] = {
  B11111100,  // 0 — segments a b c d e f on,  g off
  B01100000,  // 1 — segments b c on
  B11011010,  // 2 — segments a b d e g on
  B11110010,  // 3 — segments a b c d g on
  B01100110,  // 4 — segments b c f g on
  B10110110,  // 5 — segments a c d f g on
  B10111110,  // 6 — segments a c d e f g on
  B11100000,  // 7 — segments a b c on
  B11111110,  // 8 — all segments on
  B11100110,  // 9 — segments a b c d f g on
};

// Send one byte to the shift register and latch it to the outputs
void showDigit(byte pattern) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, pattern);
  digitalWrite(latchPin, HIGH);
}

void setup() {
  pinMode(dataPin,  OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  // Count down from 9 to 0, one second per digit
  for (byte d = 10; d > 0; d--) {
    showDigit(DIGITS[d - 1]);
    delay(1000);
  }

  // Blank the display for 2 seconds before repeating
  showDigit(B00000000);
  delay(2000);
}
