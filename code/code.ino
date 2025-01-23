
// Include Libraries
#include <RTClib.h>

//wheels
int wheel1 = 10;
int wheel2 = 9;
//led
const int ledPin = 8;

// construct objects
RTC_DS3231 rtc;  

void setup() {
  
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  pinMode (wheel1, OUTPUT);
  pinMode (wheel2, OUTPUT);
  pinMode (ledPin, OUTPUT);

}

void loop() {
wheels ();

}


void wheels () {  //Funktion för hjulen
  digitalWrite (wheel1, HIGH);
  digitalWrite (wheel2, HIGH);
  delay (1000);
  digitalWrite(wheel1, LOW);
  digitalWrite(wheel2, LOW);
  delay (1000);


}
