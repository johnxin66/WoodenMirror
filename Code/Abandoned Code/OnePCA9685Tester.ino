#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define FREQUENCY 50

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(&Wire, 0x42);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(&Wire, 0x42);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(&Wire, 0x40);

void setup() {
  Serial.begin(115200);
  
  pwm1.begin();
  pwm1.setPWMFreq(FREQUENCY);  // Analog servos run at ~50 Hz updates
  /*
  pwm2.begin();
  pwm2.setPWMFreq(FREQUENCY);
  
  pwm3.begin();
  pwm3.setPWMFreq(FREQUENCY);  // Analog servos run at ~50 Hz updates
  */
  
  Wire.setClock(400000);
  yield();
}

//approx. 90 degrees between 200 and 400
void oneServo() {
  for (int index = 0; index < 16; index++) {
    pwm1.setPWM(index, 0, 200);
    /*
    pwm2.setPWM(index, 0, 200);
    pwm3.setPWM(index, 0, 200);
    */
  }
  delay(1000);
  for (int index = 0; index < 16; index++) {
    pwm1.setPWM(index, 0, 300);
    /*
    pwm2.setPWM(index, 0, 300);
    pwm3.setPWM(index, 0, 300);
    */
  }
  delay(1000);
}

void loop() {
  //serialReceive();
  oneServo();
}
