#include <IRremoteESP8266.h>
#include <IRsend.h>

#define BAUD_RATE 115200
#define SEND_PIN 2
#define BUFF_SIZE 64

IRsend irsend(SEND_PIN);  // An IR led is controlled by GPIO pin 2

char inputBuffer[BUFF_SIZE];

void setup() {
  Serial.begin(BAUD_RATE);
  irsend.begin();
}

void loop() {
  static byte idx = 0;
  
  if (Serial.available() > 0) {
    char c = Serial.read();

    // If end of line character is received or the buffer is full
    if (c == '\n' || idx == BUFF_SIZE - 1) {
      inputBuffer[idx] = '\0';  // Null terminate the C-string.
      handleSerialCommand(inputBuffer);
      idx = 0;  // Reset the index for next time.
    } else {
      inputBuffer[idx++] = c;  // Store the character and increment the index.
    }
  }
}

void handleSerialCommand(char* command) {
  if (strcmp(command, "25 on") == 0) {
    uint64_t signals[] = {0x47D74AA7, 0xF28BB0F};
    sendIRSignals(signals, 2);
  } else if (strcmp(command, "25 off") == 0) {
    uint64_t signals[] = {0x62FAF987, 0xF28BB0F};
    sendIRSignals(signals, 2);
  } else if (strcmp(command, "26 on") == 0) {
    uint64_t signals[] = {0x1CA26B71, 0x75AD039D};
    sendIRSignals(signals, 2);
  } else if (strcmp(command, "26 off") == 0) {
    uint64_t signals[] = {0x37C61A51, 0x75AD039D};
    sendIRSignals(signals, 2);
  } else if (strcmp(command, "27 on") == 0) {
    uint64_t signals[] = {0xD7134F55, 0xDCF81559};
    sendIRSignals(signals, 2);
  } else if (strcmp(command, "27 off") == 0) {
    uint64_t signals[] = {0xF236FE35, 0xDCF81559};
    sendIRSignals(signals, 2);
  } else if (strcmp(command, "28 on") == 0) {
    uint64_t signals[] = {0x4E07A3C1, 0x860DDFCD};
    sendIRSignals(signals, 2);
  } else if (strcmp(command, "28 off") == 0) {
    uint64_t signals[] = {0x692B52A1, 0x860DDFCD};
    sendIRSignals(signals, 2);
  }
}

void sendIRSignals(uint64_t* signals, int length) {
  for (int i = 0; i < length; i++) {
    irsend.sendNEC(signals[i], 32);  // Send the IR signal.
    if (i < length - 1) {
      delay(40);  // Wait for 40 ms between signals, as per your captured data.
    }
  }
  Serial.println("Signal sent");
}
