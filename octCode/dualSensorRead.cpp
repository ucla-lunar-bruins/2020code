
// create 3 functions 
// init, read left and read right 

#include "Adafruit_VL53L0X.h"
#include "dualSensorRead.h"

// objects for the vl53l0x
//Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
//Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

void initSensors(hex address1, hex address1, int shutdownPin1, int shutdownPin2, Adafruit_VL53L0X lox1, Adafruit_VL53L0X lox2){
	// address we will assign if dual sensor is present
	#define LOX1_ADDRESS address1 //0x30
	#define LOX2_ADDRESS address2 //0x31

	// set the pins to shutdown
	#define SHT_LOX1 shutdownPin1
	#define SHT_LOX2 shutdownPin2

	/*
	    Reset all sensors by setting all of their XSHUT pins low for delay(10), then set all XSHUT high to bring out of reset
	    Keep sensor #1 awake by keeping XSHUT pin high
	    Put all other sensors into shutdown by pulling XSHUT pins low
	    Initialize sensor #1 with lox.begin(new_i2c_address) Pick any number but 0x29 and it must be under 0x7F. Going with 0x30 to 0x3F is probably OK.
	    Keep sensor #1 awake, and now bring sensor #2 out of reset by setting its XSHUT pin high.
	    Initialize sensor #2 with lox.begin(new_i2c_address) Pick any number but 0x29 and whatever you set the first sensor to
	 */
	void setID() {
	  // all reset
	  digitalWrite(SHT_LOX1, LOW);    
	  digitalWrite(SHT_LOX2, LOW);
	  delay(10);
	  // all unreset
	  digitalWrite(SHT_LOX1, HIGH);
	  digitalWrite(SHT_LOX2, HIGH);
	  delay(10);

	  // activating LOX1 and reseting LOX2
	  digitalWrite(SHT_LOX1, HIGH);
	  digitalWrite(SHT_LOX2, LOW);

	  // initing LOX1
	  if(!lox1.begin(LOX1_ADDRESS)) {
	    Serial.println(F("Failed to boot first VL53L0X"));
	    while(1);
	  }
	  delay(10);

	  // activating LOX2
	  digitalWrite(SHT_LOX2, HIGH);
	  delay(10);

	  //initing LOX2
	  if(!lox2.begin(LOX2_ADDRESS)) {
	    Serial.println(F("Failed to boot second VL53L0X"));
	    while(1);
	  }
	}

	void setup() {
	  Serial.begin(115200);

	  // wait until serial port opens for native USB devices
	  while (! Serial) { delay(1); }

	  pinMode(SHT_LOX1, OUTPUT);
	  pinMode(SHT_LOX2, OUTPUT);

	  Serial.println("Shutdown pins inited...");

	  digitalWrite(SHT_LOX1, LOW);
	  digitalWrite(SHT_LOX2, LOW);

	  Serial.println("Both in reset mode...(pins are low)");
	  
	  
	  Serial.println("Starting...");
	  setID();
	}

	setup()
 
}

int readSensor(Adafruit_VL53L0X lox) {
	VL53L0X_RangingMeasurementData_t measure;
	int sensor
  
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  
    // print sensor one reading
    Serial.print("1: ");
    if(measure1.RangeStatus != 4) {     // if not out of range
      sensor = measure1.RangeMilliMeter;    
      Serial.print(sensor);
      Serial.print("mm");  
      return sensor  
    } 

    else {
      Serial.print("Out of range");
      return -1
    }
}




