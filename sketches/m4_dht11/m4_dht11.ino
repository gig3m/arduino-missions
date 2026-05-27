// m4_dht11.ino — Mission 4 · DHT11 Weather Station (BONUS)
// The DHT11 sensor measures temperature AND humidity at the same time.
// Open the Serial Monitor and watch the numbers update every 2 seconds.
//
// IMPORTANT: You need the SimpleDHT library installed first!
// Arduino IDE → Tools → Manage Libraries → search "SimpleDHT" → Install
//
// Wiring:
//   DHT11 left pin (–)  → GND
//   DHT11 middle pin    → pin 2
//   DHT11 right pin (+) → 5V

#include <SimpleDHT.h>

const int dhtPin = 2; // DHT11 data wire

SimpleDHT11 dht11(dhtPin);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 Weather Station ready!");
  Serial.println("------------------------------");
}

void loop() {
  byte temperature = 0;
  byte humidity    = 0;
  int  err         = SimpleDHTErrSuccess;

  err = dht11.read(&temperature, &humidity, NULL);

  if (err != SimpleDHTErrSuccess) {
    Serial.print("Read failed, err=");
    Serial.println(err);
  } else {
    Serial.print("Temperature: ");
    Serial.print((int)temperature);
    Serial.print(" °C    Humidity: ");
    Serial.print((int)humidity);
    Serial.println(" %");
  }

  delay(2000); // DHT11 needs at least 1 second between readings
}
