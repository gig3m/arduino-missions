/*
  Mission 1 - First Light
  Blinks an LED that YOU placed on the breadboard.
  The LED is wired to pin 8 (through a resistor) and to GND.
*/

int ledPin = 8;   // our LED is connected to pin 8

void setup() {
  pinMode(ledPin, OUTPUT);   // get pin 8 ready to power the LED
}

void loop() {
  digitalWrite(ledPin, HIGH);  // LED ON
  delay(500);                  // wait half a second
  digitalWrite(ledPin, LOW);   // LED OFF
  delay(500);                  // wait half a second
}
