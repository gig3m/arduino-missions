// m3_beep — Active Buzzer
// Arduino Missions · Mission 3, Build 1
//
// The active buzzer makes its own sound — just switch it on and off.
// Buzzer + leg → pin 12.  Buzzer – leg → GND.

const int BUZZER = 12;  // pin connected to the + leg of the active buzzer

void setup() {
  pinMode(BUZZER, OUTPUT);  // we're sending a signal OUT to the buzzer
}

void loop() {
  // Beep pattern: slow → medium → fast → long pause

  // Three slow beeps
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER, HIGH);  // buzzer ON
    delay(500);
    digitalWrite(BUZZER, LOW);   // buzzer OFF
    delay(500);
  }

  // Three fast beeps
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(100);
  }

  // One long beep
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);

  // Quiet pause before repeating
  delay(2000);
}
