/*
  Demonstrate turns
*/
#include "turnFunctions2.h"


// Arduino like analogWrite
// value has to be between 0 and valueMax


void setup() {
  // Setup timer and attach timer to a led pin
  
}

void loop() {
  // set the brightness on LEDC channel 0

  //moving the motors forward
  moveForward(10, 150);
  turnLeft(90, 175);
  delay(1000);
  moveForward(5, 150);
  turnRight(90, 100);
  delay(1000);

  

}
