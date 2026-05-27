// Mission 5 · Weather Station
// Reads a thermistor on A0 and shows the temperature on the LCD.
//
// Wiring:
//   Thermistor: one leg → 5V, other leg → A0 AND through a 10kΩ resistor → GND
//   LCD RS  → Arduino pin 7
//   LCD E   → Arduino pin 8
//   LCD D4  → Arduino pin 9
//   LCD D5  → Arduino pin 10
//   LCD D6  → Arduino pin 11
//   LCD D7  → Arduino pin 12
//   LCD VSS → GND, LCD VDD → 5V, LCD R/W → GND
//   LCD VO  → potentiometer wiper (middle leg)
//   LCD A   → 5V, LCD K → GND
//   Potentiometer outer legs → 5V and GND

#include <LiquidCrystal.h>
#include <math.h>

// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int THERMISTOR_PIN = A0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Thermometer");
  delay(1000);
}

void loop() {
  // Read the raw analog value (0–1023)
  int rawReading = analogRead(THERMISTOR_PIN);

  // Convert to temperature using Steinhart-Hart equation
  // (same math as the kit's Lesson 15 example)
  double tempK = log(10000.0 * ((1024.0 / rawReading) - 1));
  tempK = 1.0 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK)) * tempK);

  float tempC = tempK - 273.15;              // Kelvin → Celsius
  float tempF = (tempC * 9.0 / 5.0) + 32.0; // Celsius → Fahrenheit

  // Top row: Celsius
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);   // 1 decimal place
  lcd.print((char)223);  // degree symbol °
  lcd.print("C   ");     // spaces clear old digits

  // Bottom row: Fahrenheit
  lcd.setCursor(0, 1);
  lcd.print("      ");
  lcd.print(tempF, 1);
  lcd.print((char)223);
  lcd.print("F   ");

  delay(1000); // update once per second
}
