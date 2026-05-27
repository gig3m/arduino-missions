// m7_joystick.ino
// Arduino Missions — Mission 7, Build 2: Joystick Explorer
//
// Move the joystick around or push the stick down.
// The Serial Monitor shows the X position, Y position, and button state.
// Centre = ~512. Push left = lower number. Push right = higher number.
//
// Wiring:
//   Joystick VCC  → 5V
//   Joystick GND  → GND
//   Joystick VRx  → A0  (left-right)
//   Joystick VRy  → A1  (up-down)
//   Joystick SW   → pin 2  (push button)

const int X_PIN  = A0;  // left-right axis
const int Y_PIN  = A1;  // up-down axis
const int SW_PIN = 2;   // push the stick down = button

void setup() {
  // Turn on the pull-up resistor for the button pin.
  // That means: not pressed = HIGH (1), pressed = LOW (0).
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Joystick ready! Move the stick.");
}

void loop() {
  int x      = analogRead(X_PIN);   // 0–1023
  int y      = analogRead(Y_PIN);   // 0–1023
  int button = digitalRead(SW_PIN); // 1 = not pressed, 0 = pressed

  Serial.print("X: ");
  Serial.print(x);
  Serial.print("  Y: ");
  Serial.print(y);
  Serial.print("  Button: ");
  if (button == LOW) {
    Serial.println("PRESSED!");
  } else {
    Serial.println("not pressed");
  }

  delay(200);  // print five times a second — easy to read
}
