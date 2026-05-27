// m4_distance_alarm.ino — Mission 4 · Distance Alarm
// HC-SR04 ultrasonic sensor measures distance.
// If something gets closer than 15 cm → buzzer beeps!
// No library needed — we talk to the sensor directly.
//
// Wiring:
//   HC-SR04 VCC → 5V   GND → GND
//   HC-SR04 Trig → pin 12
//   HC-SR04 Echo → pin 11
//   Active buzzer (+) → pin 8    buzzer (–) → GND

const int trigPin  = 12; // sends the ultrasonic pulse
const int echoPin  = 11; // listens for the echo
const int buzzerPin = 8; // active buzzer — just HIGH/LOW to beep

const int alarmDistance = 15; // beep if object is closer than this (cm)

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600); // open Serial Monitor to watch the distance!
}

long measureCm() {
  // 1. Make sure Trig starts LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // 2. Send a 10-microsecond HIGH pulse on Trig
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 3. Measure how long Echo stays HIGH (the round-trip time)
  long duration = pulseIn(echoPin, HIGH);

  // 4. Convert time to centimetres (sound travels ~58 µs per cm round-trip)
  long cm = duration / 58;
  return cm;
}

void loop() {
  long cm = measureCm();

  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm");

  if (cm > 0 && cm < alarmDistance) {
    digitalWrite(buzzerPin, HIGH); // BEEP!
  } else {
    digitalWrite(buzzerPin, LOW);  // quiet
  }

  delay(100); // check 10 times per second
}
