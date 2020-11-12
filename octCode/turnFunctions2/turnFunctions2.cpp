#include  "turnFunctions2.h"
#define  LEDC_CHANNEL_0     0
#define  LEDC_CHANNEL_1     1
#define  IN1 0
#define  IN2 4
#define  IN3 18
#define  IN4 5
// use 13 bit precission for LEDC timer
#define   LEDC_TIMER_13_BIT      13

// use 5000 Hz as a LEDC base frequency
#define   LEDC_BASE_FREQ     5000

// fade LED PIN (replace with LED_BUILTIN constant for built-in LED)
#define   LED_PIN            2
#define   ENB     19

int brightness    = 0;    // how bright the LED is
int fadeAmount    = 5;    // how many points to fade the LED by         

void  setupFunction   (){
  ledcSetup    (LEDC_CHANNEL_0      , LEDC_BASE_FREQ    , LEDC_TIMER_13_BIT     );
  ledcAttachPin    (LED_PIN   , LEDC_CHANNEL_0    );

  ledcSetup    (LEDC_CHANNEL_1    , LEDC_BASE_FREQ    , LEDC_TIMER_13_BIT     );
  ledcAttachPin   (ENB , LEDC_CHANNEL_1    );


  pinMode   (IN3 , OUTPUT  );
  pinMode   (IN4 , OUTPUT  );
  digitalWrite    (IN3 , LOW );
  digitalWrite    (IN4 , HIGH  );
}


void   ledcAnalogWrite    (uint8_t   channel   , uint32_t   value  , uint32_t    valueMax  ) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t   duty  = (8191 / valueMax  ) * min (value, valueMax  );

  // write duty to LEDC
  ledcWrite   (channel   , duty  );
}

void  moveForward    (int steps  , int  mspeed   ){
  int counter1   = 0;
  int counter2   = 0;
  digitalWrite    (IN1 , HIGH  );
  digitalWrite    (IN2 , LOW  );

  digitalWrite    (IN3 , HIGH );
  digitalWrite    (IN4 , LOW );
  while (steps  > counter1   && steps > counter2   ) {
    if (steps  > counter1   ) {
      ledcAnalogWrite     (LEDC_CHANNEL_0    , mspeed  );
    }
    else {
      ledcAnalogWrite     (LEDC_CHANNEL_0     , 0);
    }
    if (steps > counter2  ) {
      ledcAnalogWrite    (LEDC_CHANNEL_1     , mspeed  );
    }
    else {
      ledcAnalogWrite    (LEDC_CHANNEL_1    , 0);
    }
  }
  ledcAnalogWrite    (LEDC_CHANNEL_0    , 0);
  ledcAnalogWrite    (LEDC_CHANNEL_1    , 0);
  counter1   = 0;
  counter2   = 0;
}

void  turnRight  (int steps  , int  mspeed  ) {
  int counter1   = 0;
  int counter2   = 0;
  digitalWrite    (IN1 , HIGH  );
  digitalWrite    (IN2 , LOW  );

  digitalWrite    (IN3 , LOW );
  digitalWrite    (IN4 , HIGH );
  while (steps > counter1   && steps  > counter2   ) {
    if (steps  > counter1  ) {
      ledcAnalogWrite    (LEDC_CHANNEL_0     , mspeed  );
    }
    else {
      ledcAnalogWrite    (LEDC_CHANNEL_0     , 0);
    }
    if (steps > counter2   ) {
      ledcAnalogWrite    (LEDC_CHANNEL_1     , mspeed  );
    }
    else {
      ledcAnalogWrite     (LEDC_CHANNEL_1    , 0);
    }
  }
  ledcAnalogWrite     (LEDC_CHANNEL_0    , 0);
  ledcAnalogWrite    (LEDC_CHANNEL_1    , 0);
  counter1   = 0;
  counter2   = 0;
}

void turnLeft   (int  steps  , int  mspeed   ) {
  int counter1   = 0;
  int counter2   = 0;
  digitalWrite    (IN1 , LOW );
  digitalWrite    (IN2 , HIGH );

  digitalWrite    (IN3 , HIGH  );
  digitalWrite    (IN4 , LOW );
  while (steps  > counter1   && steps  > counter2   ) {
    if (steps  > counter1   ) {
      ledcAnalogWrite     (LEDC_CHANNEL_0     , mspeed   );
    }
    else {
      ledcAnalogWrite    (LEDC_CHANNEL_0     , 0);
    }
    if (steps  > counter2   ) {
      ledcAnalogWrite     (LEDC_CHANNEL_1    , mspeed  );
    }
    else {
      ledcAnalogWrite    (LEDC_CHANNEL_1    , 0);
    }
  }
  ledcAnalogWrite    (LEDC_CHANNEL_0    , 0);
  ledcAnalogWrite    (LEDC_CHANNEL_1    , 0);
  counter1   = 0;
  counter2   = 0;
}
