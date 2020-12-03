
// create 3 functions 
// init, read left and read right 

#include "Adafruit_VL53L0X.h"
#include "dualSensorRead.h"

// objects for the vl53l0x
//Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
//Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();


ProximityService::ProximityService() {
  this->nSensors = 0;
}

void ProximityService::writeAll(uint8_t value) {
for (int i = 0; i < nSensors; i++) {
      digitalWrite(this->sensor_list[i].sdpin, value);    
    } 
}

void ProximityService::setID(uint8_t index) {
    // all reset

    this->writeAll(LOW);
    
    delay(10);
    // all unreset
    this->writeAll(HIGH);
    delay(10);

    this->writeAll(LOW);

    digitalWrite(this->sensor_list[index].sdpin, HIGH);
    if(this->sensor_list[index].sensor->begin(LOX1_ADDRESS)) {
      Serial.print(F("F2B"));
      Serial.println(index);
      while(1);
    }
}


void ProximityService::addSensor(Adafruit_VL53L0X& lox1,  uint8_t sdpin, uint8_t address) {
  this->sensor_list[this->nSensors] = {sdpin, address,&lox1};
  this->nSensors++;
}

/*
      Reset all sensors by setting all of their XSHUT pins low for delay(10), then set all XSHUT high to bring out of reset
      Keep sensor #1 awake by keeping XSHUT pin high
      Put all other sensors into shutdown by pulling XSHUT pins low
      Initialize sensor #1 with lox.begin(new_i2c_address) Pick any number but 0x29 and it must be under 0x7F. Going with 0x30 to 0x3F is probably OK.
      Keep sensor #1 awake, and now bring sensor #2 out of reset by setting its XSHUT pin high.
      Initialize sensor #2 with lox.begin(new_i2c_address) Pick any number but 0x29 and whatever you set the first sensor to
   */
  
void ProximityService::initSensors(){
    Serial.begin(115200);

    // wait until serial port opens for native USB devices
    while (! Serial) { delay(1); }

    for (int8_t i = 0; i < this->nSensors; i++) {
        pinMode(this->sensor_list[i].sdpin, OUTPUT);
        digitalWrite(SHT_LOX1, LOW);

    }
    Serial.println("Starting...");
    for (int8_t i = 0; i < this-nSensors; i++) {
      setID(i);
    }
	}


int ProximityService::readSensor(Adafruit_VL53L0X& lox) {
	 int8_t sensor = 0;
  
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  
    // print sensor one reading
    Serial.print("1: ");
    if(measure.RangeStatus != 4) {     // if not out of range
      sensor = measure.RangeMilliMeter;    
      return sensor;  
    } 

    else {
      Serial.print("OOR");
      return -1;
    }
}
