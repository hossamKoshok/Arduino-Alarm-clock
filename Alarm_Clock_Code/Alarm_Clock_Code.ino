

#include <Wire.h>
#include <EEPROM.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>

#define LED_PIN 5
#define NUM_LEDS 3
#define BRIGHTNESS 255
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc;
int HOUR, MINUT, SECOND;
bool flag = true;
bool alarmflag = true;
int current_second;
int current_minut;
int page = 0;
int Alarm1[2] = { 0, 0 };
int Alarm2[2] = { 0, 0 };

#define UpdateEvery 1
#define buttonPin 4
#define button2 3
#define button3 2
#define horn 10

int buttonState;                     // the current reading from the input pin
int lastButtonState = LOW;           // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Wire.begin();
  rtc.begin();
  lcd.begin(16, 2);

  pinMode(buttonPin, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(horn, OUTPUT);

  lcd.backlight();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2014, 1, 21, 23, 59, 30));
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  lcd.clear();
  fill_solid( leds, NUM_LEDS, CRGB::Black);
  while (page == 0) {
    buttonSwitch();
    DisplayingTime();
  }
  lcd.clear();
  while (page == 1) {
    buttonSwitch();
    setAlarm1();
  }
  lcd.clear();
  while (page == 2) {
    buttonSwitch();
    setAlarm2();
  }
  while (page == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Alarm Ringing..");
    fill_solid( leds, NUM_LEDS, CRGB::Red);
    AlarmRing();
    fill_solid( leds, NUM_LEDS, CRGB::Yellow);
    AlarmRing();
    fill_solid( leds, NUM_LEDS, CRGB::Red);
    AlarmRing();
    fill_solid( leds, NUM_LEDS, CRGB::Yellow);
    AlarmRing();
    fill_solid( leds, NUM_LEDS, CRGB::Black);
    alarmflag = false;
    page = 0;
  }
}

void DisplayingTime() {
  DateTime now = rtc.now();
  HOUR = now.hour();
  MINUT = now.minute();
  SECOND = now.second();

  if (Alarm1[0] == HOUR && Alarm1[1] == MINUT && alarmflag) {
    page = 3;
    current_minut = MINUT;
  }
  if (Alarm2[0] == HOUR && Alarm2[1] == MINUT && alarmflag) {
    page = 3;
    current_minut = MINUT;
  }
  if (current_minut != MINUT) {
    alarmflag = true;
  }
  if (current_second != SECOND) {
    flag = true;
  }

  if (SECOND % UpdateEvery == 0 && flag) {

    if (SECOND == 0) {
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Time:");
    lcd.setCursor(6, 0);
    lcd.print(HOUR, DEC);
    lcd.print(":");
    lcd.print(MINUT, DEC);
    lcd.print(":");
    lcd.print(SECOND, DEC);
    lcd.setCursor(0, 1);
    lcd.print("Date: ");
    lcd.print(now.day(), DEC);
    lcd.print("/");
    lcd.print(now.month(), DEC);
    lcd.print("/");
    lcd.print(now.year(), DEC);
    current_second = SECOND;
    flag = false;
  }
}

void buttonSwitch() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        page++;
        if (page > 2) { page = 0; }
      }
    }
  }
  lastButtonState = reading;
}
void setAlarm1() {
  lcd.setCursor(2, 0);
  lcd.print("Set Alarm 1");

  if (digitalRead(button2) == HIGH) {
    Alarm1[0]++;
    delay(200);
    if (Alarm1[0] > 23) {
      Alarm1[0] = 0;
      lcd.clear();
    }
  }
  if (digitalRead(button3) == HIGH) {
    Alarm1[1]++;
    delay(200);
    if (Alarm1[1] > 59) {
      Alarm1[1] = 0;
      lcd.clear();
    }
  }

  lcd.setCursor(0, 1);
  lcd.print("Time:");
  lcd.setCursor(6, 1);
  lcd.print(Alarm1[0], DEC);
  lcd.print(":");
  lcd.print(Alarm1[1], DEC);
}
void setAlarm2() {
  lcd.setCursor(2, 0);
  lcd.print("Set Alarm 2");

  if (digitalRead(button2) == HIGH) {
    Alarm2[0]++;
    delay(200);
    if (Alarm2[0] > 23) {
      Alarm2[0] = 0;
      lcd.clear();
    }
  }
  if (digitalRead(button3) == HIGH) {
    Alarm2[1]++;
    delay(200);
    if (Alarm2[1] > 59) {
      Alarm2[1] = 0;
      lcd.clear();
    }
  }

  lcd.setCursor(0, 1);
  lcd.print("Time:");
  lcd.setCursor(6, 1);
  lcd.print(Alarm2[0], DEC);
  lcd.print(":");
  lcd.print(Alarm2[1], DEC);
}

void AlarmRing() {
  int x;
  digitalWrite(horn, HIGH);
  for (int i = 0; i < 500; i++) {
    if (digitalRead(button2) == HIGH) {
      alarmflag = false;
      page = 0;
      break;
    }
    delay(1);
  }
  digitalWrite(horn, LOW);
  for (int i = 0; i < 500; i++) {
    if (digitalRead(button2) == HIGH) {
      alarmflag = false;
      page = 0;
      break;
    }
    delay(1);
  }
}
