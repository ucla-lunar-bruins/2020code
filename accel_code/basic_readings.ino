// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;


const int MPU = 0x68;
float yaw = 0;
float GyroZ, gyroAngleZ, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;

float read_yaw() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  previousTime = currentTime;

  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000;
  
  
  GyroZ = (g.gyro.z);
  
  GyroZ = GyroZ;
  //Serial.println(GyroZ);

  yaw = yaw + GyroZ * elapsedTime;
  //Serial.println(elapsedTime);
  return yaw;
}

float calculate_IMU_error() {
    while (c < 200) {
        Wire.beginTransmission(MPU);
        Wire.write(0x47);
        Wire.requestFrom(MPU, 2, true);
        
        GyroZ = Wire.read() << 8 | Wire.read();

        Serial.print(GyroZ);

        GyroErrorZ = GyroErrorZ + (GyroZ);

        c++;
        delay(10);
    }
    GyroErrorZ = GyroErrorZ / 200;
    return GyroErrorZ;
}

void setup() {

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
  
  delay(1000);
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  calculate_IMU_error();
  delay(1000);
}

void loop() {


  /* Get new sensor events with the readings */
  Serial.print("yaw: ");
  Serial.println(read_yaw());

  delay(10);
}
