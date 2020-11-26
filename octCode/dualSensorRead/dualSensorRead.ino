#include "Arduino.h"
#include "dualSensorRead.h"
#include "constants.h"


Adafruit_VL53L0X lox1, lox2;

void setup() {

  initSensors(lox1,lox2);
}

void loop() {

  Serial.println(readSensor(lox1));
  delay(10);
  
}
