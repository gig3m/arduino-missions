// Mission 6 · Servo Wave
// The servo sweeps back and forth like it's waving at you.
// Signal wire → pin 9. Power: red → 5V, brown → GND.

#include <Servo.h>

Servo myservo;   // this object controls the servo

int pos = 0;     // current angle (0–180 degrees)

void setup() {
  myservo.attach(9);  // signal wire is plugged into pin 9
}

void loop() {
  // Sweep from 0 degrees to 180 degrees
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);  // move to this angle
    delay(15);           // wait 15 ms so the servo can keep up
  }

  // Sweep back from 180 degrees to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}
