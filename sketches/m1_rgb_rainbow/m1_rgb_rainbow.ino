/*
  Mission 1 Bonus - Rainbow Light
  One LED that can glow ANY color by mixing red, green, and blue light.
  Wiring matches the kit: RED leg -> pin 6, GREEN leg -> pin 5, BLUE leg -> pin 3.
  The longest leg is the "minus" leg and goes to GND.
*/

int redPin   = 6;
int greenPin = 5;
int bluePin  = 3;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

// Mix a color. Each number is 0 (off) to 255 (brightest).
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void loop() {
  setColor(255, 0, 0);     delay(1000);  // red
  setColor(0, 255, 0);     delay(1000);  // green
  setColor(0, 0, 255);     delay(1000);  // blue
  setColor(255, 255, 0);   delay(1000);  // yellow
  setColor(128, 0, 255);   delay(1000);  // purple
  setColor(255, 255, 255); delay(1000);  // white
}
