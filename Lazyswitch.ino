/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6ZUHH5Ckp"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "OLWOR8jpIJWyvTCQhKHKTpCoRjBcPLzB"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
//#########################################################################
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "M3314";
char pass[] = "";

const int ledPin = 2;  // Pin for built-in LED (may vary depending on the board)
// The LED on Pin 2 is somehow fucked so LOW means on while HIGH means off.

Servo servo1;  // for pin 16
Servo servo2;  // for pin 5

int buzzerPin = 14;  // any digital pin
int buzzerState = LOW;

// Data wire is connected to the GPIO12 pin of the ESP8266
#define ONE_WIRE_BUS 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Ultrasound module pins
#define TRIG_PIN 15
#define ECHO_PIN 13

long duration;
float speedOfSound;
int distance;

BLYNK_WRITE(V2) {
  servo1.write(param.asInt());
}
BLYNK_WRITE(V3) {
  servo2.write(param.asInt());
}
BLYNK_WRITE(V1) {
  buzzerState = param.asInt();
}

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Add the readDHT11 function definition here
void readDHT11() {
  float tempC2 = dht.readTemperature();
  float humidity = dht.readHumidity();

  //if (isnan(tempC2) || isnan(humidity)) {
  //  Serial.println("Failed to read from DHT11 sensor!");
  //  return;
  //}

  Blynk.virtualWrite(V5, tempC2);
  Blynk.virtualWrite(V6, humidity);
}

#define LDR_PIN 13
int ldrValue;

//#########################################################################
void setup() { 
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledPin, LOW);  // Turn LED on when attempting to connect
    delay(500);
    digitalWrite(ledPin, HIGH);  // Turn LED off when attempting to connect
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(ledPin, LOW);  // Turn LED on when connected

  servo1.attach(16);
  servo2.attach(5);

  Blynk.virtualWrite(V2, 150);
  Blynk.virtualWrite(V3, 150);
  servo1.write(150);
  servo2.write(150);

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);  // Set LED pin as output

  // Initialize the DS18B20 sensor
  sensors.begin();

  // Initialize the ultrasound module pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  dht.begin();

  pinMode(LDR_PIN, INPUT);
}
//#########################################################################
void loop() {
  Blynk.run();

  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(ledPin, HIGH);  // Turn LED off when connected to save power
  } else {
    digitalWrite(ledPin, LOW);  // Turn LED on when not connected
  }

  if (buzzerState == HIGH) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // Read temperature data from the DS18B20 sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  // Send temperature data to Blynk
  Blynk.virtualWrite(V0, tempC);

  //Read the temp and humidity data from DHT11 sensor
  readDHT11();

  //Read the LDR LM393 module for ambient light data
  ldrValue = digitalRead(LDR_PIN);
  Blynk.virtualWrite(V7, ldrValue);  

  // Adjust the speed of sound based on temperature
  if (tempC == -127) {
    tempC = 25;
  }
  speedOfSound = 331.4 + (0.6 * tempC);

  // Measure distance using ultrasound module
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * (speedOfSound / 10000) / 2;

  // Send distance data to Blynk
  Blynk.virtualWrite(V4, distance);
  //Serial.print(distance);

  // Activate switch if distance is less than 10 cm for over 2 seconds
  static unsigned long startTime = 0;
  static bool switchActivated = false;

  if (distance < 10) {
    if (startTime == 0) {
      startTime = millis();
    } else if (millis() - startTime > 500) {
      switchActivated = true;
    }
  } else {
    startTime = 0;
    switchActivated = false;
  }

  // Switch off V2 and V3 if switch is activated and one or both of them is on
  if (switchActivated && (servo1.read() == 150 || servo2.read() == 150)) {
    if (servo1.read() == 150) {
      Blynk.virtualWrite(V2, 30);
      servo1.write(30);
    }
    if (servo2.read() == 150) {
      Blynk.virtualWrite(V3, 30);
      servo2.write(30);
    }
    switchActivated = false;
    delay(800);
  }

  // Switch on V2 and V3 if switch is activated and both of them are off
  if (switchActivated && servo1.read() == 30 && servo2.read() == 30) {
    Blynk.virtualWrite(V2, 150);
    servo1.write(150);
    Blynk.virtualWrite(V3, 150);
    servo2.write(150);
    switchActivated = false;
    delay(800);
  }

  //Serial.print(distance);
  delay(100);
}