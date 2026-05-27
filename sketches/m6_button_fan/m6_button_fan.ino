// Mission 6 · Button Fan
// Press the button to turn the fan on. Press again to turn it off.
//
// L293D motor driver chip connections:
//   ENABLE (pin 1 of L293D) → Arduino pin 5  (PWM speed control)
//   IN_A   (pin 2 of L293D) → Arduino pin 3  (direction)
//   IN_B   (pin 7 of L293D) → Arduino pin 4  (direction)
//
// Button → Arduino pin 2 (other leg to GND, INPUT_PULLUP active)
// Motor power: use the 9V power module on the breadboard.

#define ENABLE 5   // PWM speed pin → L293D pin 1
#define IN_A   3   // direction pin A → L293D pin 2
#define IN_B   4   // direction pin B → L293D pin 7

#define BUTTON_PIN 2   // push button (press to GND)

bool fanOn = false;          // is the fan running?
bool lastButtonState = HIGH; // previous button reading

void setup() {
  pinMode(ENABLE, OUTPUT);
  pinMode(IN_A,   OUTPUT);
  pinMode(IN_B,   OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // internal pull-up; not pressed = HIGH

  // Start with fan off
  analogWrite(ENABLE, 0);
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // Detect the moment the button is pressed (HIGH → LOW edge)
  if (lastButtonState == HIGH && buttonState == LOW) {
    fanOn = !fanOn;   // toggle: if it was on, turn it off; if off, turn on

    if (fanOn) {
      digitalWrite(IN_A, HIGH);  // set spin direction
      digitalWrite(IN_B, LOW);
      analogWrite(ENABLE, 200);  // spin at ~78% speed (0–255)
    } else {
      analogWrite(ENABLE, 0);    // stop the motor
    }

    delay(50);  // small pause to ignore button bounce
  }

  lastButtonState = buttonState;
}
