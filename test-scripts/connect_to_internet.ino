#include <ESP8266WiFi.h>

// Network SSID
const char* ssid = "M3314";
const char* password = "";
const int ledPin = 2; // Pin for built-in LED (may vary depending on the board)
// The LED on Pin 2 is somehow fucked so LOW means on while HIGH means off.

void setup() {
  
  Serial.begin(115200);
  delay(10);
 
  // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Galen_ESP8266");
  WiFi.begin(ssid, password);
  
  pinMode(ledPin, OUTPUT); // Set LED pin as output

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledPin, LOW); // Turn LED on when attempting to connect
    delay(500);
    digitalWrite(ledPin, HIGH); // Turn LED off when attempting to connect
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(ledPin, LOW); // Turn LED on when connected
}
 
void loop() {
  if(WiFi.status() == WL_CONNECTED){
    digitalWrite(ledPin, LOW); // Turn LED on when connected
  }else{
    digitalWrite(ledPin, HIGH); // Turn LED off when not connected
  }
}
