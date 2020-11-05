#include "proximity.h"
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void proxInit() {

  // wait until serial port opens for native USB devices
  if (!lox.begin()) {
    //Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
}

int range_mm() {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); 
     if (measure.RangeStatus != 4) {  // phase failures have incorrect data
      return (int)Serial.println(measure.RangeMilliMeter);
     }   else {
    	return -1;
   }
}

