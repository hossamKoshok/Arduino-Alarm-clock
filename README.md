# ⏰ Arduino Smart Alarm Clock

A customizable smart alarm clock built using Arduino. This project features a real-time clock (RTC) module, an LCD display, and buttons to set and manage alarms. Ideal for learning embedded systems and creating your own DIY smart clock.

## 🧰 Features

- 🕰️ Real-time timekeeping using RTC (DS3231)
- 🔔 Alarm functionality with buzzer
- 🖥️ Time and alarm display on 16x2 LCD
- 🎛️ User interface with buttons for setting time and alarms
- 🌡️ Optional: Temperature display from RTC module
- 💡 Optional: LED indication when alarm is triggered

## 🧱 Components Used

| Component             | Quantity |
|----------------------|----------|
| Arduino UNO/Nano     | 1        |
| DS3231 RTC Module     | 1        |
| 16x2 LCD Display (I2C preferred) | 1 |
| Buzzer               | 1        |
| Push Buttons         | 3        |
| LEDs (optional)      | 1-2      |
| Resistors (220Ω)     | As needed |
| Breadboard & Wires   | As needed |

## 🔌 Wiring Overview

> LCD → I2C SDA/SCL to A4/A5 (for UNO)  
> RTC → SDA/SCL to A4/A5  
> Buttons → Digital pins (with pull-down or pull-up resistors)  
> Buzzer → Digital pin  
> LEDs → Digital pins

Refer to `wiring_diagram.png` for the full circuit diagram.

## 💻 How It Works

- The RTC module keeps track of current time even when the Arduino is powered off.
- The LCD displays the current time and set alarm.
- Buttons are used to:
  - Set current time
  - Set alarm time
  - Enable/disable the alarm
- When current time matches the alarm time, the buzzer and optional LED are activated.
- Optional: Add snooze functionality or save alarm settings in EEPROM.

CAD Files:https://grabcad.com/library/arduino-clock-with-horn-1
