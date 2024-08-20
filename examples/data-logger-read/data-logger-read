/*  papagayo-iot 
 *  read
 *  RTC control on DS1307, alarms and events control, DS18B20 temperature sensor control and EEPROM r/w operations
 *  Check the documentation at https://github.com/adafruit/RTClib
 *  https://github.com/PaulStoffregen/TimeAlarms
 *  https://github.com/PaulStoffregen/OneWire
 *  https://github.com/milesburton/Arduino-Temperature-Control-Library
 *  https://github.com/cyberp/AT24Cx 
 *  This example code has a MIT License.
 *  Modified 31 Jul 2024
 *  By quijanov
 */
#include <Wire.h> 
#include "RTClib.h" //1 rtc control
#include "TimeAlarms.h" 
#include "Time.h" //2 alarms and events control
//#include "OneWire.h"
//#include "DallasTemperature.h" //3 temperature sensor control
#include "AT24CX.h" //4 EEPROM r/w

const int kOneWirePin = 5;

struct md {
  DateTime hora_fecha;
  float temperatura;  
} MyData; //data structure for data logger 


RTC_DS1307 rtc; //rtc instance
AT24C32 EepromRTC; //eeprom instance

//OneWire oneWireBus(kOneWirePin); //init bus
//DallasTemperature sensor(&oneWireBus); //init sensor

uint8_t segundo,minuto,hora,dia,mes;
uint16_t anio;

// put your setup code here, to run once:
void setup() {

  Serial.begin(9600);
  
  //sensor.begin(); //temperature sensor init
  
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
  readEEPROM();
}

// put your main code here, to run repeatedly:
void loop() {
  while (1==1){} //run once
}
/*
 * EEPROM read data logg
 */
void readEEPROM() {
  Serial.println("reading data-logg on EEPROM...");
  //format hh:mm:ss dd/mm/aaaa
  hora = EepromRTC.read(0); // posiscion 1:ocupa 1 byte
  print2digits(hora);
  Serial.write(":");
  minuto = EepromRTC.read(1); // posiscion 2:ocupa 1 byte
  print2digits(minuto);
  Serial.write(":");
  segundo = EepromRTC.read(2); // posiscion 3: ocupa 1 byte
  print2digits(segundo);
  Serial.write("    ");
  dia = EepromRTC.read(3); // posiscion 4:ocupa 1 byte
  Serial.print(dia, DEC);
  Serial.write("/");
  mes = EepromRTC.read(4); // posiscion 5:ocupa 1 byte
  Serial.print(mes, DEC);
  Serial.write("/");  
  anio = EepromRTC.readInt(5); // posiscion 6:ocupa 2 bytes 
  Serial.print(anio, DEC);
  Serial.write("    ");
  float temperatura = EepromRTC.readFloat(7); // posiscion 8:ocupa 4 bytes
  Serial.println(temperatura, 2);
}
/*
 * helper function to serial print
 */
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
