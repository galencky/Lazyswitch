#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t kRecvPin = 16; // Connected to GPIO 4 (D2)
const uint16_t kCaptureBufferSize = 1024;
const uint16_t kMinUnknownSize = 1;
const uint8_t kTimeout = 15; // Decrease the timeout to make it more sensitive

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);

decode_results results;  // Stores the results

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 bps
  irrecv.enableIRIn();   // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    irrecv.resume();  // Receive the next value
  }
  // Remove or decrease this delay if your remote sends signals more frequently
  // delay(100);
}
