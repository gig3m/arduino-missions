// Arduino Missions — Mission 2: Button Switch
// Press button A (pin 9) → LED on.
// Press button B (pin 8) → LED off.
// Pins match the Elegoo kit Lesson 5 wiring.

int ledPin     = 5;   // LED (long leg → 220Ω → pin 5)
int buttonApin = 9;   // Button A — press to turn LED ON
int buttonBpin = 8;   // Button B — press to turn LED OFF

void setup() {
  pinMode(ledPin,     OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  // no resistor needed — pull-up built in
  pinMode(buttonBpin, INPUT_PULLUP);
}

void loop() {
  // INPUT_PULLUP means: not pressed = HIGH, pressed = LOW
  if (digitalRead(buttonApin) == LOW) {
    digitalWrite(ledPin, HIGH);   // button A pressed → LED on
  }
  if (digitalRead(buttonBpin) == LOW) {
    digitalWrite(ledPin, LOW);    // button B pressed → LED off
  }
}
