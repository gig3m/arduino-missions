// m7_remote_light.ino
// Arduino Missions — Mission 7, Build 3: Remote-Controlled Light
//
// Press button 1 on your remote → LED turns ON.
// Press button 2 on your remote → LED turns OFF.
//
// IMPORTANT: The codes below (BTN_ON and BTN_OFF) are examples from
// the Elegoo kit remote. YOUR remote might have different codes.
// Run the IR Remote Reader sketch first, press your chosen buttons,
// and write down the codes that appear. Then replace the numbers below.
//
// Wiring:
//   IR receiver DATA → pin 11
//   IR receiver VCC  → 5V
//   IR receiver GND  → GND
//   LED (+) long leg → 220Ω resistor → pin 6
//   LED (–) short leg → GND

#include <IRremote.hpp>

const int IR_PIN  = 11;  // IR receiver data pin
const int LED_PIN = 6;   // LED pin (PWM, but we just use HIGH/LOW here)

// Button codes from the Elegoo kit remote.
// Replace these with YOUR remote's codes if they don't work!
const uint32_t BTN_ON  = 0xF30CFF00;  // button "1" on the kit remote
const uint32_t BTN_OFF = 0xE718FF00;  // button "2" on the kit remote

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // start with LED off

  Serial.begin(9600);
  Serial.println("Remote Light ready!");
  Serial.println("Press button 1 (ON) or button 2 (OFF) on your remote.");

  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;

    // Print what we received so you can check the codes
    Serial.print("Received: 0x");
    Serial.println(code, HEX);

    if (code == BTN_ON) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("→ LED ON");
    } else if (code == BTN_OFF) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("→ LED OFF");
    }

    IrReceiver.resume();  // ready for the next signal
  }
}
