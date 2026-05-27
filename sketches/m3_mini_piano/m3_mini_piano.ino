// m3_mini_piano — Passive Buzzer + Two Buttons
// Arduino Missions · Mission 3, Build 2
//
// Passive buzzer → pin 12.
// Button A → pin 9 (INPUT_PULLUP, pressed = LOW).
// Button B → pin 8 (INPUT_PULLUP, pressed = LOW).
//
// Press button A → play note C4 (262 Hz).
// Press button B → play note E4 (330 Hz).
// Press both      → play note G4 (392 Hz) — a chord note!
// Release all     → silence.

// Note frequencies (Hz) — no extra library needed
// (Using NOTE_ prefix to avoid clashing with Arduino's A4 pin constant.)
const int NOTE_C4 = 262;
const int NOTE_D4 = 294;
const int NOTE_E4 = 330;
const int NOTE_F4 = 349;
const int NOTE_G4 = 392;
const int NOTE_A4 = 440;
const int NOTE_B4 = 494;
const int NOTE_C5 = 523;

const int BUZZER  = 12;  // passive buzzer + leg
const int BUTTON_A =  9;  // left button
const int BUTTON_B =  8;  // right button

void setup() {
  pinMode(BUTTON_A, INPUT_PULLUP);  // built-in pull-up; pressed = LOW
  pinMode(BUTTON_B, INPUT_PULLUP);
  // buzzer pin needs no pinMode for tone()
}

void loop() {
  bool pressedA = (digitalRead(BUTTON_A) == LOW);
  bool pressedB = (digitalRead(BUTTON_B) == LOW);

  if (pressedA && pressedB) {
    tone(BUZZER, NOTE_G4);   // both buttons → G
  } else if (pressedA) {
    tone(BUZZER, NOTE_C4);   // button A → C
  } else if (pressedB) {
    tone(BUZZER, NOTE_E4);   // button B → E
  } else {
    noTone(BUZZER);     // nothing pressed → silence
  }
}
