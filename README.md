# ESP32 Smart Home Control System

A simple and modern IoT Smart Home Project using ESP32 that allows you to control 4 Lights and 1 Fan from a web interface.

---

🚀 Features

- 💡 Control 4 Lights (ON/OFF)

- 🌬️ Control 1 Fan (ON/OFF)
- 📱 Mobile Friendly Web UI
- ⚡ Fast real-time control (no page reload)
- 🎨 Modern animated button design
- 📡 Works with ESP32 Access Point (No router needed)

## 🧰 Hardware Required

- ESP32 Development Board
- 4 Relay Module (for lights)
- 1 Relay Module (for fan)
- Jumper wires
- Power supply (5V / 12V depending on relay setup)
- Bulbs / Fan load
- 🔌 GPIO Connection
- Device	ESP32 GPIO
- Light 1	23
- Light 2	22
- Light 3	21
- Light 4	19
- Fan	18


## 📡 How It Works
- ESP32 creates its own WiFi network
- You connect your phone to ESP32 WiFi
- Open browser and enter IP
- Control devices from web buttons


## 🌐 Default WiFi Info
- SSID: `WIFI`
- Password: (none / open network)

## 📍 Access Web Panel

After connecting to ESP32 WiFi, 

open:http://192.168.4.1

🖥️ Web UI Preview

Dark modern interface 🌙

Glow effect buttons ✨

Large mobile-friendly controls 📱

Smooth hover animations 🎯


## ⚙️ Installation Steps

 Open Arduino IDE

 Install ESP32 board package
 
Select correct board (ESP32 Dev Module)
Upload the code
 
Power ESP32

Connect WiFi and open IP


## 📦 Libraries Used

WiFi.h

WebServer.h


(No external libraries required)

## 🔥 Future Improvements

📊 Real-time device status sync

🎤 Voice control (Google Assistant / Jarvis)

🌍 Internet-based control (Firebase / Blynk)

## 📈 Mobile App version

🔐 Password protected admin panel

----- 
