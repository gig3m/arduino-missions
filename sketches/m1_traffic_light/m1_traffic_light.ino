/*
  Mission 1 Project - Traffic Light
  Three LEDs take turns like a real traffic light:
  green (go), yellow (get ready), red (stop), over and over.
  green  -> pin 8
  yellow -> pin 9
  red    -> pin 10
*/

int greenPin  = 8;
int yellowPin = 9;
int redPin    = 10;

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  // GREEN - go!
  digitalWrite(greenPin, HIGH);
  delay(3000);
  digitalWrite(greenPin, LOW);

  // YELLOW - get ready to stop
  digitalWrite(yellowPin, HIGH);
  delay(1000);
  digitalWrite(yellowPin, LOW);

  // RED - stop!
  digitalWrite(redPin, HIGH);
  delay(3000);
  digitalWrite(redPin, LOW);
}
