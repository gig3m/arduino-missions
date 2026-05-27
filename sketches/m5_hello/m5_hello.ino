// Mission 5 · Hello Screen
// Shows your name on a 16x2 LCD display.
//
// Wiring (match the kit's Lesson 14 image):
//   LCD RS  → Arduino pin 7
//   LCD E   → Arduino pin 8
//   LCD D4  → Arduino pin 9
//   LCD D5  → Arduino pin 10
//   LCD D6  → Arduino pin 11
//   LCD D7  → Arduino pin 12
//   LCD VSS → GND
//   LCD VDD → 5V
//   LCD R/W → GND
//   LCD VO  → potentiometer wiper (middle leg)
//   LCD A   → 5V  (backlight +)
//   LCD K   → GND (backlight –)
//   Potentiometer outer legs → 5V and GND

#include <LiquidCrystal.h>

// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // Tell the library: 16 columns, 2 rows
  lcd.begin(16, 2);

  // Row 0 (top): your name
  lcd.setCursor(0, 0);
  lcd.print("Hello, Levi!");    // <-- change "Levi" to YOUR name

  // Row 1 (bottom): a greeting
  lcd.setCursor(0, 1);
  lcd.print("You built this!");
}

void loop() {
  // Nothing to do — the LCD holds the message on its own.
}
