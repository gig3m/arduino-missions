// Arduino Missions — Mission 2: Knob Dimmer
// Turn the potentiometer knob to make the LED brighter or dimmer.
// Pot wiper (middle leg) → A0.
// LED (long leg → 220Ω → pin 6).

int potPin = A0;  // potentiometer wiper
int ledPin = 6;   // LED — pin 6 is a PWM pin (~)

void setup() {
  pinMode(ledPin, OUTPUT);
  // A0 is an analog input — no pinMode needed
}

void loop() {
  // analogRead gives 0–1023. analogWrite needs 0–255.
  // Divide by 4 to scale: 1023 / 4 = 255.
  int brightness = analogRead(potPin) / 4;
  analogWrite(ledPin, brightness);
}
