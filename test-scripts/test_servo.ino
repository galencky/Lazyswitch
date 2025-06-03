#include <ESP8266WiFi.h>
#include <Servo.h>

// Servo motor pins
int servoPin1 = 16; // Connect servo motor 1 to this pin
int servoPin2 = 5;  // Connect servo motor 2 to this pin

Servo servo1;
Servo servo2;

void setup() {
  // Initialize servo motors
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  // Set initial positions
  servo1.write(0);
  servo2.write(0);
}

void loop() {
  // Sweep servo motor 1 from 0 to 180 degrees
  for (int pos = 0; pos <= 360; pos++) {
    servo1.write(pos);
    delay(15);
  }

  // Sweep servo motor 1 from 180 to 0 degrees
  for (int pos = 360; pos >= 0; pos--) {
    servo1.write(pos);
    delay(15);
  }

  // Sweep servo motor 2 from 0 to 180 degrees
  for (int pos = 0; pos <= 360; pos++) {
    servo2.write(pos);
    delay(15);
  }

  // Sweep servo motor 2 from 180 to 0 degrees
  for (int pos = 360; pos >= 0; pos--) {
    servo2.write(pos);
    delay(15);
  }
}
