#include "Adafruit_VL53L0X.h"


#define SHT_LOX1 6
#define SHT_LOX2 7
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31


class ProximityService {
  public:
    ProximityService();
    void initSensors();

    void addSensor(Adafruit_VL53L0X& lox1, uint8_t sdpin, uint8_t address);

    int readSensor(Adafruit_VL53L0X& lox); 
  private:

    void setID(uint8_t input);
    struct SensorInfo {
        uint8_t sdpin;
        uint8_t address; 
        Adafruit_VL53L0X* sensor;
    };

    void writeAll(uint8_t value);
    VL53L0X_RangingMeasurementData_t measure;
    SensorInfo sensor_list[4];
    uint8_t nSensors;
};
