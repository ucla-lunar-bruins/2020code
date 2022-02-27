  #include <Arduino.h>


#define FORWARD 1
#define BACKWARD -1
#define STOP  0

#define ENA_F 5
#define ENB_F 6

#define IN1_F 4
#define IN2_F 3
#define IN3_F 8
#define IN4_F 7

#define ENA_B 9
#define ENB_B 10

#define IN1_B 11
#define IN2_B 12
#define IN3_B 13
#define IN4_B 2

#define MAX_SPEED_RAD 5.23598775 
#define MAX_SPEED_RPM 50

#define MAX_SPEED_MPS .157077


#define WHEEL_CIRCUMFERENCE_CM 22


 
#define MAX_CMPS  18.26
#define MAX_MSPCM 54.7645125958379
#define COOLDOWN_TIME  200





void setupMovement()
{
  pinMode(ENA_F, OUTPUT);
  pinMode(ENB_F, OUTPUT);

  pinMode(IN1_F, OUTPUT);
  pinMode(IN2_F, OUTPUT);
  pinMode(IN3_F, OUTPUT);
  pinMode(IN4_F, OUTPUT);

  pinMode(ENA_B, OUTPUT);
  pinMode(ENB_B, OUTPUT);

  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(IN3_B, OUTPUT);
  pinMode(IN4_B, OUTPUT);
}


void turnDegrees(double degrees){
    float initialYaw = read_yaw();
    float targetYaw = initialYaw - degrees;
 
    while(abs(read_yaw() - targetYaw) > .05){
        // turning left
        digitalWrite(IN1_F, HIGH);
        digitalWrite(IN2_F, HIGH);
        digitalWrite(IN3_F, LOW);
        digitalWrite(IN4_F, LOW);
        
        digitalWrite(IN1_B, HIGH);
        digitalWrite(IN2_B, HIGH);
        digitalWrite(IN3_B, LOW);
        digitalWrite(IN4_B, LOW);
    }
    stop();
 
    Serial.println("turnDegrees");
    Serial.print("Initial Yaw: ");
    Serial.println(initialYaw);
    Serial.print("Target Yaw: ");
    Serial.println(targetYaw);
    Serial.print("Final Yaw: ");
    Serial.println(read_yaw());
}

void setup() {
  Serial.begin(9600);
  setupMovement();
  turnDegrees(90)
}

void loop () {}
