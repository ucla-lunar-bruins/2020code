#include "proximity.h"


void setup() {
  Serial.begin(115200);

  
  //Serial.println("VL53L0X API Simple Ranging example\n\n"); 
}


void loop() {
  Serial.println("Hello");
  Serial.println(range_mm());

  delay(100);
}
