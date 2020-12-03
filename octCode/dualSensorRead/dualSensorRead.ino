#include "Arduino.h"
#include "dualSensorRead.h"
#include "constants.h"


Adafruit_VL53L0X leftSensor, rightSensor;
ProximityService ps;


void setup() {

  ps.addSensor(leftSensor, SHT_LOX1,  LOX1_ADDRESS);
  ps.addSensor(rightSensor, SHT_LOX2, LOX2_ADDRESS);
  ps.initSensors();
}

void loop() {

  Serial.println(ps.readSensor(leftSensor));
  //Serial.println(ps.readSensor(rightSensor));
  delay(10);
  
}
