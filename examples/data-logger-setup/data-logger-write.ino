/*  papagayo-iot 
 *  data-logger-write
 *  RTC control on DS1307, alarms and events control, DS18B20 temperature sensor and EEPROM r/w operations
 *  Check the documentation at https://github.com/adafruit/RTClib
 *  https://github.com/PaulStoffregen/TimeAlarms
 *  https://github.com/PaulStoffregen/OneWire
 *  https://github.com/milesburton/Arduino-Temperature-Control-Library
 *  https://github.com/cyberp/AT24Cx 
 *  This example code has a MIT License.
 *  Modified 6 Aug 2024
 *  By quijanov
 */
#include <Wire.h> 
#include "RTClib.h" //1 rtc control
#include "TimeAlarms.h" 
#include "Time.h" //2 alarms and events control
#include "OneWire.h"
#include "DallasTemperature.h" //3 temperature sensor control
#include "AT24CX.h" //4 EEPROM r/w

const int kOneWirePin = 5;
const word kMaxBytes = 4095; 
const int kMaxWrites = 1;

struct md {
  DateTime hora_fecha;
  float temperatura;  
} MyData; //data structure for data logger


RTC_DS1307 rtc; //rtc instance
AT24C32 EepromRTC; //eeprom instance

OneWire oneWireBus(kOneWirePin); //init bus
DallasTemperature sensor(&oneWireBus); //init sensor

// put your setup code here, to run once:
void setup() {
  Serial.begin(9600);
  sensor.begin(); //temperature sensor init
  
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
  
  setTime(18,00,0,8,8,24); // set time to 17:50:00 at 8/8/2024
  //alarms and events
  Alarm.timerOnce(10, sensorReadEvent);  //alarm time, 10s before  
}

// put your main code here, to run repeatedly:
void loop() {
  Alarm.delay(1000); //wait 1000ms for no apparent reason..
}
/*
 * read temperature sensor 
 */
void sensorReadEvent() {
  sensor.requestTemperatures();
  MyData.temperatura = sensor.getTempCByIndex(0); //temperature
  MyData.hora_fecha = rtc.now(); //real time clock
  writeEEPROM(); //write data
}
/*
 * EEPROM save data logg
 */
void writeEEPROM() {
  Serial.println("writing data-logg on EEPROM...");
  //format hh:mm:ss dd/mm/aaaa
  EepromRTC.write(0, MyData.hora_fecha.hour()); // position 1: 1 byte
  EepromRTC.write(1, MyData.hora_fecha.minute()); // position 2: 1 byte
  EepromRTC.write(2, MyData.hora_fecha.second()); // position 3: 1 byte
  EepromRTC.write(3, MyData.hora_fecha.day()); // position 4: 1 byte
  EepromRTC.write(4, MyData.hora_fecha.month()); // position 5: 1 byte
  EepromRTC.writeInt(5, MyData.hora_fecha.year()); // position 6:2 bytes 
  EepromRTC.writeFloat(7, MyData.temperatura); // position 8: 4 bytes   
}
