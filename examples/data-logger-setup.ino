/*  papagayo-iot 
 *  setup
 *  Real time settings RTC on DS1307
 *  Check the documentation at https://github.com/adafruit/RTClib
 *  This example code is in a MIT License.
 *  Modified 25 Jul 2024
 *  By quijanov
 */
 
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup () {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC"); //serious error
    Serial.flush();
    abort();
  }
  Serial.println("date and time settings...");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("DS1307 fixed at!");
  Serial.print("time = ");
  Serial.println(__TIME__);

  Serial.print("date = ");
  Serial.print(__DATE__);
}

void loop () {
}
