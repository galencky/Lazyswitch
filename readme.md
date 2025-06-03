
# 🛏️ LazySwitch: Bedside Light & AC Controller with ESP8266 + Blynk

![Platform](https://img.shields.io/badge/platform-ESP8266-blue)
![Blynk](https://img.shields.io/badge/Blynk-enabled-green)
![License: MIT](https://img.shields.io/badge/license-MIT-lightgrey)

A DIY IoT project to control your room lights, monitor your AC, and wake up your roommate — **without leaving your bed**.

This project uses an **ESP8266**, **Blynk app**, and some clever hardware hacks:
- **Servos** to physically flip light switches.
- **Ultrasound sensor** as a hands-free toggle.
- **Temperature & humidity sensors** to monitor AC performance.
- **Buzzer** to annoy or wake your roommate.
- All controlled via your **phone** using the Blynk app!

---

## 🔧 Features

| Feature                  | Description                                                              |
|--------------------------|--------------------------------------------------------------------------|
| 💡 Servo-Controlled Switches | Servos mounted on wall switches to toggle lights remotely              |
| 📱 Blynk App Integration    | Remote control interface for phone-based operation                     |
| 🌡️ AC Monitor (Temp & Humidity) | DS18B20 and DHT11 provide real-time room environment data             |
| ✋ Touchless Ultrasound Switch | Waves under 10 cm trigger servo toggle (automates wall switch press) |
| 🔔 Buzzer Alarm             | Remotely trigger buzzer to wake roommate or signal                      |
| 🔦 LDR for Ambient Light    | Detect light/dark (currently logs data only, no auto logic)             |
| 📶 WiFi LED Indicator       | LED blinks during connection, turns off once WiFi is connected          |

---

## 📷 Setup Overview

```

\[Phone: Blynk App]
⇅ WiFi
\[ESP8266 Board] ──→ Servo1 (Light Switch A)
──→ Servo2 (Light Switch B)
──→ Buzzer (Roommate Alarm)
──→ DHT11 (Temp & Humidity)
──→ DS18B20 (Accurate Temp)
──→ Ultrasonic (Proximity Trigger)
──→ LDR (Ambient Light Monitor)

```

---

## 🛠️ Hardware Used

- ESP8266 (NodeMCU or similar)
- 2x Servo motors (SG90 or equivalent)
- DHT11 Temperature & Humidity Sensor
- DS18B20 Digital Temperature Sensor
- HC-SR04 Ultrasonic Distance Sensor
- Passive buzzer
- LDR (Light-Dependent Resistor)
- Blynk app (classic or IoT)

---

## 🧪 Pin Mapping

| Component        | GPIO Pin |
|------------------|----------|
| Servo 1          | 16       |
| Servo 2          | 5        |
| Buzzer           | 14       |
| DS18B20          | 12       |
| DHT11            | 4        |
| LDR              | 13       |
| Ultrasonic Trig  | 15       |
| Ultrasonic Echo  | 13       |
| Built-in LED     | 2        |

> ⚠️ Note: Some pins are double-used (e.g., GPIO13), may need adjustment depending on your board.

---

## 🚀 Getting Started

### 1. Install Dependencies
In Arduino IDE or PlatformIO:
- ESP8266 board support
- Libraries:
  - Blynk
  - ESP8266WiFi
  - Servo
  - OneWire
  - DallasTemperature
  - DHT sensor library

### 2. Configure Blynk
- Create a new template on [Blynk](https://blynk.io)
- Get:
  - `BLYNK_TEMPLATE_ID`
  - `BLYNK_TEMPLATE_NAME`
  - `BLYNK_AUTH_TOKEN`
- Add virtual pins:
  - V0: DS18B20 temp
  - V1: Buzzer toggle
  - V2/V3: Servo angles
  - V4: Distance (ultrasound)
  - V5: DHT11 temp
  - V6: DHT11 humidity
  - V7: LDR (digital)

### 3. Upload & Power On
- Flash the code to your ESP8266
- Power with USB or 5V wall adapter
- Open Blynk app and start toggling light switches from bed 😎

---

## 📸 Demo

*(Insert GIFs, photos, or a YouTube link of your setup in action)*

---

## 📋 To-Do / Ideas

- [ ] Auto-light based on LDR + Time
- [ ] IFTTT or Google Assistant voice control
- [ ] Roommate reaction log 🤣
- [ ] OTA update support

---

## 📄 License

MIT License – use freely, but don’t forget to get out of bed sometimes.

---

## 🙌 Acknowledgements

Inspired by pure laziness and the need for smarter living spaces.  
Built with 💡 and ☕ by [Kuan-Yuan Chen](https://github.com/galencky)
