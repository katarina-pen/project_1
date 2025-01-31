
// Include Libraries
#include <RTClib.h>  //clock
#include <Wire.h>    // also clock
#include "U8glib.h"  // smol screen
#include "LedControl.h"

//set alarm time
int as = 40;
int am = 25;
int ah = 11;

//wheels
int wheel1 = 8;
int wheel2 = 9;
//led
const int ledPin = 7;

// construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC

//display
LedControl lc = LedControl(12, 13, 10, 1);

void setup() {

  Serial.begin(9600);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lc.shutdown(0, false);  // Set the brightness to a medium values
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);  // and clear the display

  pinMode(wheel1, OUTPUT);
  pinMode(wheel2, OUTPUT);
  //pinMode (ledPin, OUTPUT);
}

void loop() {
  //wheels ();

  Serial.println(getTime());

  showTime();
  delay(500);
  showAlarm();
  delay(500);
  alarm ();
}


void wheels() {  //Funktion för hjulen
  digitalWrite(wheel1, HIGH);
  digitalWrite(wheel2, HIGH);
  delay(1000);
  digitalWrite(wheel1, LOW);
  digitalWrite(wheel2, LOW);
  delay(1000);
}

void showTime() {
  DateTime now = rtc.now();  //declaring "now"
  lc.setDigit(0, 0, now.second() % 10, false);
  lc.setDigit(0, 1, (now.second() - (now.second() % 10)) / 10, false);
  lc.setDigit(0, 2, now.minute() % 10, false);
  lc.setDigit(0, 3, (now.minute() - (now.minute() % 10)) / 10, false);
  lc.setDigit(0, 4, now.hour() % 10, false);
  lc.setDigit(0, 5, (now.hour() - (now.hour() % 10)) / 10, false);
}

void showAlarm() {
  DateTime now = rtc.now();  //declaring "now"
  lc.setDigit(0, 0, as % 10, false);
  lc.setDigit(0, 1, (as - (as % 10)) / 10, false);
  lc.setDigit(0, 2, am % 10, false);
  lc.setDigit(0, 3, (am - (am % 10)) / 10, false);
  lc.setDigit(0, 4, ah % 10, false);
  lc.setDigit(0, 5, (ah - (ah % 10)) / 10, false);
}

void alarm() {
  DateTime now = rtc.now();  //declaring "now"
  if(ah == now.hour() && am==now.minute() && as==now.second()){
    Serial.println("ALARM ON!!!!!!!");
    wheels();
    digitalWrite(ledPin, HIGH);
  }
}

//rtc modul- tid
String getTime() {
  DateTime now = rtc.now();
  return String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}
