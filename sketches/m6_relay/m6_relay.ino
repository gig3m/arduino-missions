// Mission 6 · Relay Click
// The relay clicks on and off — listen for the satisfying CLICK!
//
// The relay coil is driven by the L293D chip (same as the motor lesson).
// L293D connections:
//   ENABLE → Arduino pin 5  (keep HIGH to activate the driver)
//   IN_A   → Arduino pin 3  (HIGH = relay ON/click; LOW = relay OFF)
//   IN_B   → Arduino pin 4  (keep LOW)
//
// The relay coil connects to L293D Out 1 and Out 2 (or ground).
// Use the 9V power module on the breadboard.

#define ENABLE 5   // L293D enable pin
#define IN_A   3   // controls relay coil via L293D
#define IN_B   4   // held LOW

void setup() {
  pinMode(ENABLE, OUTPUT);
  pinMode(IN_A,   OUTPUT);
  pinMode(IN_B,   OUTPUT);

  digitalWrite(ENABLE, HIGH);  // always enabled
  digitalWrite(IN_B,   LOW);   // always LOW
  digitalWrite(IN_A,   LOW);   // relay starts OFF
}

void loop() {
  // Click ON
  digitalWrite(IN_A, HIGH);  // relay energizes — CLICK!
  delay(1000);               // stay on for 1 second

  // Click OFF
  digitalWrite(IN_A, LOW);   // relay releases — CLICK!
  delay(1000);               // stay off for 1 second
}
