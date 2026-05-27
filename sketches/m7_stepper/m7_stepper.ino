// m7_stepper.ino
// Arduino Missions — Mission 7, Build 4: Stepper Motor (BONUS)
//
// The stepper motor turns exactly one full revolution clockwise,
// pauses, then one full revolution counter-clockwise. Repeat.
// You can feel each tiny step — that's precise control!
//
// Wiring (ULN2003 driver board → Arduino):
//   IN1 → pin 8
//   IN2 → pin 10
//   IN3 → pin 9
//   IN4 → pin 11
//   Driver board 5–12V → 5V (use a separate power supply for heavy loads)
//   Driver board GND   → GND
//   Plug the stepper motor connector into the ULN2003 board.

#include <Stepper.h>

// The 28BYJ-48 motor needs 2048 steps for one full revolution.
const int STEPS_PER_REV = 2048;

// Pins must be in this order: 8, 10, 9, 11 (matches the ULN2003 coil sequence)
Stepper myStepper(STEPS_PER_REV, 8, 10, 9, 11);

void setup() {
  // 15 rpm is a safe, smooth speed for the 28BYJ-48. Max is about 17 rpm.
  myStepper.setSpeed(15);
  Serial.begin(9600);
  Serial.println("Stepper Motor ready!");
}

void loop() {
  Serial.println("Turning clockwise one full revolution...");
  myStepper.step(STEPS_PER_REV);   // positive = clockwise
  delay(500);

  Serial.println("Turning counter-clockwise one full revolution...");
  myStepper.step(-STEPS_PER_REV);  // negative = counter-clockwise
  delay(500);
}
