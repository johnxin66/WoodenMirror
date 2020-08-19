#include <AccelStepper.h>
#define motorPin11  2         // IN1 on the ULN2003 driver 1
#define motorPin12  3         // IN2 on the ULN2003 driver 1
#define motorPin13  4         // IN3 on the ULN2003 driver 1
#define motorPin14  5        // IN4 on the ULN2003 driver 1
#define motorPin21  6         // IN1 on the ULN2003 driver 1
#define motorPin22  7         // IN2 on the ULN2003 driver 1
#define motorPin23  8         // IN3 on the ULN2003 driver 1
#define motorPin24  9        // IN4 on the ULN2003 driver 1
#define ledpin 52
AccelStepper stepper1(4, motorPin11, motorPin13, motorPin12, motorPin14);
AccelStepper stepper2(4, motorPin21, motorPin23, motorPin22, motorPin24);

void setup() {
  stepper1.setCurrentPosition(0);
  stepper1.setMaxSpeed(500);
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, HIGH);
}

void loop() {
  stepper1.moveTo(500);
  stepper1.setSpeed(350);
  stepper1.runSpeedToPosition();
}
