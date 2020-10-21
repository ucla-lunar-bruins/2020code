/*
  Demonstrate turns
*/



#define IN1 0
#define IN2 4

#define IN3 18
#define IN4 5


// use first channel of 16 channels (started from zero)
#define LEDC_CHANNEL_0     0
#define LEDC_CHANNEL_1     1

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     5000

// fade LED PIN (replace with LED_BUILTIN constant for built-in LED)
#define LED_PIN            2
#define ENB     19

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// Arduino like analogWrite
// value has to be between 0 and valueMax
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(channel, duty);
}

void setup() {
  // Setup timer and attach timer to a led pin
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(LED_PIN, LEDC_CHANNEL_0);

  ledcSetup(LEDC_CHANNEL_1, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(ENB, LEDC_CHANNEL_1);


  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

int speed = 255;

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

void moveForward(int steps, int mspeed){
  int counter1 = 0;
  int counter2 = 0;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  while (steps > counter1 && steps > counter2) {
    if (steps > counter1) {
      ledcAnalogWrite(LEDC_CHANNEL_0, mspeed);
    }
    else {
      ledcAnalogWrite(LEDC_CHANNEL_0, 0);
    }
    if (steps > counter2) {
      ledcAnalogWrite(LEDC_CHANNEL_1, mspeed);
    }
    else {
      ledcAnalogWrite(LEDC_CHANNEL_1, 0);
    }
  }
  analogWrite(LEDC_CHANNEL_0, 0);
  analogWrite(LEDC_CHANNEL_1, 0);
  counter1 = 0;
  counter2 = 0;
}

void turnLeft(int steps, int mspeed) {
  int counter1 = 0;
  int counter2 = 0;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  while (steps > counter1 && steps > counter2) {
    if (steps > counter1) {
      ledcAnalogWrite(LEDC_CHANNEL_0, mspeed);
    }
    else {
      ledcAnalogWrite(LEDC_CHANNEL_0, 0);
    }
    if (steps > counter2) {
      ledcAnalogWrite(LEDC_CHANNEL_1, mspeed);
    }
    else {
      ledcAnalogWrite(LEDC_CHANNEL_1, 0);
    }
  }
  ledcAnalogWrite(LEDC_CHANNEL_0, 0);
  ledcAnalogWrite(LEDC_CHANNEL_1, 0);
  counter1 = 0;
  counter2 = 0;
}

void turnRight(int steps, int mspeed) {
  int counter1 = 0;
  int counter2 = 0;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  while (steps > counter1 && steps > counter2) {
    if (steps > counter1) {
      ledcAnalogWrite(LEDC_CHANNEL_0, mspeed);
    }
    else {
      ledcAnalogWrite(LEDC_CHANNEL_0, 0);
    }
    if (steps > counter2) {
      ledcAnalogWrite(LEDC_CHANNEL_1, mspeed);
    }
    else {
      ledcAnalogWrite(LEDC_CHANNEL_1, 0);
    }
  }
  ledcAnalogWrite(LEDC_CHANNEL_0, 0);
  ledcAnalogWrite(LEDC_CHANNEL_1, 0);
  counter1 = 0;
  counter2 = 0;
}
