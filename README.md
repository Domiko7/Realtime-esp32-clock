# ESP32 OLED NTP Clock

This project displays the current date and time on a 128x64 OLED display using an ESP32. The time is synchronized via NTP (Network Time Protocol) over WiFi, then WiFi is turned off to save power.

## Features

- Connects to WiFi and syncs time from an NTP server (`pool.ntp.org`)
- Displays current day, date, and time on a 128x64 OLED screen (SSD1306)
- Automatically reconnects if WiFi connection is lost during initial connection
- Turns off WiFi after time synchronization to save power
- Updates the time display every second

## Hardware Requirements

- ESP32 development board
- 128x64 OLED display (SSD1306, I2C interface)
- Connecting wires

## Software Requirements

- Arduino IDE with ESP32 board support installed
- Libraries:
  - `Adafruit_SSD1306`
  - `Adafruit_GFX`
  - `WiFi` (included with ESP32 board package)

## Wiring

| OLED Pin | ESP32 Pin               |
|----------|------------------------|
| VCC      | 3.3V                   |
| GND      | GND                    |
| SCL      | GPIO 22 (default I2C SCL) |
| SDA      | GPIO 21 (default I2C SDA) |

*Adjust pins if your setup differs.*

## Configuration

Edit the following variables in the code to match your network and time zone:

```cpp
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* ntpServer = "pool.ntp.org";

const long gmtOffset_sec = 3600;      // Adjust for your timezone (seconds offset from GMT)
const int daylightOffset_sec = 3600;  // Adjust for daylight savings time if applicable
