// m7_ir_remote.ino
// Arduino Missions — Mission 7, Build 1: IR Remote Reader
//
// Point your remote at the IR receiver and press buttons.
// Every button press prints a code in the Serial Monitor.
// Those codes are YOUR remote's secret language!
//
// Wiring:
//   IR receiver DATA pin → Arduino pin 11
//   IR receiver VCC pin  → 5V
//   IR receiver GND pin  → GND

#include <IRremote.hpp>

const int IR_PIN = 11;  // data wire from receiver goes here

void setup() {
  Serial.begin(9600);
  Serial.println("IR Remote Reader ready!");
  Serial.println("Point the remote at the sensor and press a button.");

  // Start listening on pin 11.
  // ENABLE_LED_FEEDBACK blinks the built-in LED when a signal arrives.
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  // Did we receive a signal?
  if (IrReceiver.decode()) {
    // Print the button code in hexadecimal (like 0xBA45FF00)
    Serial.print("Button code: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    // Get ready for the next signal
    IrReceiver.resume();
  }
}
