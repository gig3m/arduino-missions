// m4_tilt.ino — Mission 4 · Tilt Switch
// A ball inside the switch rolls around when you tilt the board.
// One way: the circuit closes → pin 2 reads LOW → LED turns ON.
// The other way: circuit opens → pin 2 reads HIGH → LED turns OFF.

const int switchPin = 2;   // tilt switch (ball switch)
const int ledPin    = 13;  // built-in LED on the Arduino

void setup() {
  pinMode(switchPin, INPUT_PULLUP); // pull-up so the pin reads HIGH when open
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int val = digitalRead(switchPin);

  if (val == LOW) {
    // Switch is closed (ball touching both contacts) — tilt one way
    digitalWrite(ledPin, HIGH); // LED ON
  } else {
    // Switch is open (ball rolled away) — tilt the other way
    digitalWrite(ledPin, LOW);  // LED OFF
  }
}
