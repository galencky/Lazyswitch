#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// An IR detector/demodulator is connected to GPIO pin 2(D4 on a WeMos D1 Mini).
const uint16_t kRecvPin = 2;
const int maxSignals = 1000; // the maximum number of signals that can be stored

IRrecv irrecv(kRecvPin);
decode_results results;

// Arrays to hold the captured signals and their timestamps
uint64_t capturedSignals[maxSignals];
unsigned long timestamps[maxSignals];
int signalCount = 0;
unsigned long startTime;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    // If a code is received and array isn't full, store it in the array
    if (signalCount < maxSignals) {
      if (signalCount == 0) {
        // this is the first signal received, record the start time
        startTime = millis();
      }
      capturedSignals[signalCount] = results.value;
      timestamps[signalCount] = millis() - startTime;
      signalCount++;
      irrecv.resume();  // Receive the next value
    }
  }

  // Check if we've been recording for more than 1 second
  if (signalCount > 0 && (millis() - startTime) > 1000) {
    // Dump all the signals and their timestamps to the Serial Monitor
    for (int i = 0; i < signalCount; i++) {
      Serial.print(timestamps[i]);
      Serial.print(": ");
      serialPrintUint64(capturedSignals[i], HEX);
      Serial.println("");
    }
    // Now clear the array and start over
    signalCount = 0;
  }
}
