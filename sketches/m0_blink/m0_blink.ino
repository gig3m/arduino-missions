/*
  Mission 0 - Make the Brain Blink
  This blinks the tiny light built into your Arduino (next to the letter "L").
  You do NOT need to wire anything up for this one.
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // get the built-in light ready to use
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // light ON
  delay(1000);                      // wait 1 second (1000 milliseconds)
  digitalWrite(LED_BUILTIN, LOW);   // light OFF
  delay(1000);                      // wait 1 second
}
