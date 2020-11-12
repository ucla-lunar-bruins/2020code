#include <cstdint> 
#include "Arduino.h"
void moveForward(int steps, int mspeed);
void turnLeft(int steps, int mspeed);
void turnRight(int steps, int mspeed);
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255);
void setupFunction();
