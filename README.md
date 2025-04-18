# 🚨 Arduino Smart Alarm System

A smart alarm system built with Arduino that can detect motion, monitor environmental conditions, and trigger alarms with optional notification features. Ideal for home security and IoT experimentation.

## 🔧 Features

- 🔍 Motion detection using PIR sensor
- 🌡️ Temperature and humidity monitoring (DHT11/DHT22)
- 🔊 Buzzer alert for intrusions
- 💡 LED indicator for system status
- 🕹️ Button-based system arming/disarming
- ⏰ Real-time clock (RTC) integration for time-based alarms
- 📱 Optional: Serial output or IoT-based notifications

## 📦 Hardware Used

| Component               | Quantity |
|------------------------|----------|
| Arduino UNO/Nano       | 1        |
| PIR Motion Sensor      | 1        |
| DHT11/DHT22 Sensor     | 1        |
| Buzzer                 | 1        |
| LED (Red/Green)        | 2        |
| Push Button            | 1        |
| RTC Module (DS3231)    | Optional |
| Jumper Wires, Breadboard| As needed |
| Resistors (220Ω)       | 2        |

## 🔌 Circuit Diagram

> Coming soon / Refer to `circuit_diagram.png` in the repo.

## 🧠 How It Works

1. **System Arming:** Use the push button to toggle the alarm system on or off.
2. **Motion Detection:** When armed, the PIR sensor detects movement.
3. **Alarm Triggering:** On detection, the buzzer activates and an LED flashes.
4. **Environmental Monitoring:** The DHT sensor continuously reads temperature and humidity.
5. **Real-time Data:** If RTC is connected, logs are timestamped.

## 📂 File Structure


CAD Files:https://grabcad.com/library/arduino-clock-with-horn-1
