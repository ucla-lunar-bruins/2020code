#include "Adafruit_VL53L0X.h"


#define SHT_LOX1 6
#define SHT_LOX2 7
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31


class ProximityService {
  public:
    ProximityService();
    void initSensors(Adafruit_VL53L0X& lox1, Adafruit_VL53L0X& lox2);

    void addSensor(Adafruit_VL53L0X& lox1, uint8_t sdpin, uint8_t address);

    int readSensor(Adafruit_VL53L0X& lox); 
  private:

    void setID(Adafruit_VL53L0X& lox1, Adafruit_VL53L0X& lox2);
    struct SensorInfo {
        Adafruit_VL53L0X* sensor;
        uint8_t sdpin;
        uint8_t address; 
    };

    VL53L0X_RangingMeasurementData_t measure;
    SensorInfo sensor_list[10];
    int nSensors;
};
