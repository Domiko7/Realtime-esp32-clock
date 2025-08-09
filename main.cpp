#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* ntpServer = "pool.ntp.org";

const long gmtOffset_sec = 3600; // the + seconds you want from GMT timezone (etc. if you're in GMT+1 -> 3600 sec)
const int daylightOffset_sec = 3600;

void reconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connection lost, trying to reconnect...");
    WiFi.disconnect(true);
    WiFi.begin(ssid, password);

    unsigned long startAttemptTime = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
      Serial.println(".");
      delay(500);
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Successfully reconnected");
    } else {
      Serial.println("Failed to reconnect!");
    }
  }
}

void displayTime() {
  struct tm timeInfo;

  if (!getLocalTime(&timeInfo)) {
    Serial.println("Failed to obtain time!");
    return;
  }

  char day[30];
  char date[30];
  char time[30];
  strftime(day, sizeof(day), "%A, %B %d", &timeInfo);
  strftime(date, sizeof(date), "%m/%d/%Y", &timeInfo);
  strftime(time, sizeof(time), "%H:%M:%S", &timeInfo);


  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setTextSize(1);
  display.setCursor(5, 10);
  display.println(day);

  display.setTextSize(1);
  display.setCursor(30, 25);
  display.println(date);

  display.setTextSize(2);
  display.setCursor(15, 40);
  display.println(time);

  display.display();


}

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Connecting with SSD1306 failed, check your wiring");
  }

  display.clearDisplay();
  display.display();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  reconnect();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeInfo;
  while (!getLocalTime(&timeInfo)) {
    delay(500);
    Serial.println(".");
  }

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

}

void loop() {
  displayTime();
  delay(1000);
}
