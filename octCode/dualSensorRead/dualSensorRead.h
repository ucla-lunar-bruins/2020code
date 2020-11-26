#include "Adafruit_VL53L0X.h"

#define SHT_LOX1 6
#define SHT_LOX2 7
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

void initSensors(Adafruit_VL53L0X& lox1, Adafruit_VL53L0X& lox2);

int readSensor(Adafruit_VL53L0X& lox); 
