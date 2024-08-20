/*  papagayo-iot 
 *  dt-log-erase
 *  RTC control on DS1307, alarms and events control, DS18B20 temperature sensor control and EEPROM r/w operations
 *  Check the documentation at https://github.com/adafruit/RTClib
 *  https://github.com/PaulStoffregen/TimeAlarms
 *  https://github.com/PaulStoffregen/OneWire
 *  https://github.com/milesburton/Arduino-Temperature-Control-Library
 *  https://github.com/cyberp/AT24Cx 
 *  This example code has a MIT License.
 *  Modified 5 Aug 2024
 *  By quijanov
 */
#include <Wire.h> 
#include "RTClib.h" //1 rtc control
//#include "TimeAlarms.h" 
//#include "Time.h" //2 alarms and events control
//#include "OneWire.h"
//#include "DallasTemperature.h" //3 temperature sensor control
#include "AT24CX.h" //4 EEPROM r/w

const int kOneWirePin = 5;
const word kMaxBytes = 4095; 
int count_elms = 0;

struct md {
  DateTime hora_fecha;
  float temperatura;  
} MyData; //data structure for data logger 


RTC_DS1307 rtc; //rtc instance
AT24C32 EepromRTC; //eeprom instance

uint8_t segundo,minuto,hora,dia,mes;
uint16_t anio;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC"); //serious error Oo
    Serial.flush();
    abort();
  }
  if (!rtc.isrunning()) { //maybe after a power lose or not previous set
    Serial.println("RTC is NOT running, let's fix the new time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  } else { 
    Serial.println("RTC is ok..");
  }  
  
    eraseEEPROM();    
}

// put your main code here, to run repeatedly:
void loop() {
  while (1==1){} //run once
}

/*
 * EEPROM erase data logg
 */
void eraseEEPROM() {
  EepromRTC.write(0, 0); // posiscion 0:ocupa 1 byte
  EepromRTC.write(1, 0); // posiscion 1:ocupa 1 byte
  EepromRTC.write(2, 0); // posiscion 2: ocupa 1 byte
  EepromRTC.write(3, 0); // posiscion 3:ocupa 1 byte
  EepromRTC.write(4, 0); // posiscion 4:ocupa 1 byte
  EepromRTC.writeInt(5, 0); // posiscion 5:ocupa 2 bytes 
  EepromRTC.writeFloat(7, 0.0); // posiscion 7:ocupa 4 bytes
  Serial.println("EEPROM erased!");  
}
