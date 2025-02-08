/*
* Name: Alarm clock
* Author: Katarina Penava
* Date: 2025-02-08
* Description: 
*/


// Include Libraries
#include <RTClib.h>  //clock
#include <Wire.h>    // also clock
#include "U8glib.h"  // smol screen
#include "LedControl.h"

//set alarm time
int as = 00;
int am = 55;
int ah = 21;

//wheels
int wheel1 = 8;
int wheel2 = 9;

//led
const int ledPin = 7;

//knappar
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int buttonPin3 = 6;

// boolean variable
bool AlarmState = false;

// construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC

//display
LedControl lc = LedControl(12, 13, 10, 1);

void setup() {

  Serial.begin(9600);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lc.shutdown(0, false);  
  lc.setIntensity(0, 0); // Set the brightness to the lowest value
  lc.clearDisplay(0);  // and clear the display

  //wheels
  pinMode(wheel1, OUTPUT);
  pinMode(wheel2, OUTPUT);
  //led
  pinMode (ledPin, OUTPUT);
 
 
  //knappar
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode (buttonPin2, INPUT_PULLUP);
  pinMode (buttonPin3, INPUT_PULLUP);
}

void loop() {
 Serial.println(getTime());
  buttons ();

  if (digitalRead(buttonPin3) == LOW) {
    //delay (500);
    showAlarm(); 
    AlarmState = !AlarmState;  
    while(digitalRead(buttonPin3) == LOW);
  }

  if (AlarmState) {
    showAlarm();  // If true, show alarm
  } else {
    showTime();   // If false, show time
  }

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

void blink () { //function for led
  for (int i=0; i<5; i++);{
    digitalWrite(ledPin, HIGH);
    delay (500);
    digitalWrite (ledPin, LOW);
    delay (500);
  }
}

void showTime() {    // button 3??
  DateTime now = rtc.now();  //declaring "now"
  lc.setDigit(0, 0, now.second() % 10, false);
  lc.setDigit(0, 1, (now.second() - (now.second() % 10)) / 10, false);
  lc.setDigit(0, 2, now.minute() % 10, true);
  lc.setDigit(0, 3, (now.minute() - (now.minute() % 10)) / 10, false);
  lc.setDigit(0, 4, now.hour() % 10, true);
  lc.setDigit(0, 5, (now.hour() - (now.hour() % 10)) / 10, false);
}

void showAlarm() {
  DateTime now = rtc.now();  //declaring "now"
  lc.setDigit(0, 0, as % 10, false);
  lc.setDigit(0, 1, (as - (as % 10)) / 10, false);
  lc.setDigit(0, 2, am % 10, true);
  lc.setDigit(0, 3, (am - (am % 10)) / 10, false);
  lc.setDigit(0, 4, ah % 10, true);
  lc.setDigit(0, 5, (ah - (ah % 10)) / 10, false);
}

void alarm() {
  DateTime now = rtc.now();  //declaring "now"
  if(ah == now.hour() && am==now.minute() && as==now.second()){
    Serial.println("ALARM ON!!!!!!!");
    wheels();
    blink ();
    
  }
}

//rtc modul- tid
String getTime() {
  DateTime now = rtc.now();
  return String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}


void buttons () { //button 1???
  //hours
  if (digitalRead(buttonPin1) == LOW) { // low or high?
    delay (500);
    ah = ah+1 ;      //lc.setDigit ???
  }

  if (ah > 23) {  //hour går ej över 23
    ah = 0;
    }
  //while (digitalRead(buttonPin1) == LOW);



  //minutes
  if (digitalRead(buttonPin2) == LOW) { 
    delay (500);
    am = am+1; 
  }

  if (am > 59) {  //minute går ej över 59
    am = 0;
    ah= ah +1 ;
    }
  //while (digitalRead(buttonPin2) == LOW);
}
