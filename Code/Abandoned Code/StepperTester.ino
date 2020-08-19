#include <AccelStepper.h>
#include <ArduinoJson.h>

const int kPinButton = 53;
// Motor pin definition
#define motorPin11  2         // IN1 on the ULN2003 driver 1
#define motorPin12  3         // IN2 on the ULN2003 driver 1
#define motorPin13  4         // IN3 on the ULN2003 driver 1
#define motorPin14  5        // IN4 on the ULN2003 driver 1
#define motorPin21  6         // IN1 on the ULN2003 driver 2
#define motorPin22  7         // IN2 on the ULN2003 driver 2
#define motorPin23  8         // IN3 on the ULN2003 driver 2
#define motorPin24  9        // IN4 on the ULN2003 driver 2
#define motorPin31  10         // IN1 on the ULN2003 driver 3
#define motorPin32  11         // IN2 on the ULN2003 driver 3
#define motorPin33  12         // IN3 on the ULN2003 driver 3
#define motorPin34  13        // IN4 on the ULN2003 driver 3
#define motorPin41  14         // IN1 on the ULN2003 driver 4
#define motorPin42  15         // IN2 on the ULN2003 driver 4
#define motorPin43  16         // IN3 on the ULN2003 driver 4
#define motorPin44  17        // IN4 on the ULN2003 driver 4
#define motorPin51  18         // IN1 on the ULN2003 driver 5
#define motorPin52  19         // IN2 on the ULN2003 driver 5
#define motorPin53  20         // IN3 on the ULN2003 driver 5
#define motorPin54  21        // IN4 on the ULN2003 driver 5
#define motorPin61  22         // IN1 on the ULN2003 driver 6
#define motorPin62  23         // IN2 on the ULN2003 driver 6
#define motorPin63  24         // IN3 on the ULN2003 driver 6
#define motorPin64  25        // IN4 on the ULN2003 driver 6
#define motorPin71  26         // IN1 on the ULN2003 driver 7
#define motorPin72  27         // IN2 on the ULN2003 driver 7
#define motorPin73  28         // IN3 on the ULN2003 driver 7
#define motorPin74  29        // IN4 on the ULN2003 driver 7
#define motorPin81  30         // IN1 on the ULN2003 driver 8
#define motorPin82  31         // IN2 on the ULN2003 driver 8
#define motorPin83  32         // IN3 on the ULN2003 driver 8
#define motorPin84  33        // IN4 on the ULN2003 driver 8
#define motorPin91  34         // IN1 on the ULN2003 driver 9
#define motorPin92  35         // IN2 on the ULN2003 driver 9
#define motorPin93  36         // IN3 on the ULN2003 driver 9
#define motorPin94  37        // IN4 on the ULN2003 driver 9

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(4, motorPin11, motorPin13, motorPin12, motorPin14);
AccelStepper stepper2(4, motorPin21, motorPin23, motorPin22, motorPin24);
AccelStepper stepper3(4, motorPin31, motorPin33, motorPin32, motorPin34);
AccelStepper stepper4(4, motorPin41, motorPin43, motorPin42, motorPin44);
AccelStepper stepper5(4, motorPin51, motorPin53, motorPin52, motorPin54);
AccelStepper stepper6(4, motorPin61, motorPin63, motorPin62, motorPin64);
AccelStepper stepper7(4, motorPin71, motorPin73, motorPin72, motorPin74);
AccelStepper stepper8(4, motorPin81, motorPin83, motorPin82, motorPin84);
AccelStepper stepper9(4, motorPin91, motorPin93, motorPin92, motorPin94);
 
void setup() {
  Serial.begin(115200);
  stepper1.setCurrentPosition(0);
  stepper1.setMaxSpeed(500);
  stepper2.setCurrentPosition(0);
  stepper2.setMaxSpeed(500);
  stepper3.setCurrentPosition(0);
  stepper3.setMaxSpeed(500);
  stepper4.setCurrentPosition(0);
  stepper4.setMaxSpeed(500);
  stepper5.setCurrentPosition(0);
  stepper5.setMaxSpeed(500);
  stepper6.setCurrentPosition(0);
  stepper6.setMaxSpeed(500);
  stepper7.setCurrentPosition(0);
  stepper7.setMaxSpeed(500);
  stepper8.setCurrentPosition(0);
  stepper8.setMaxSpeed(500);
  stepper9.setCurrentPosition(0);
  stepper9.setMaxSpeed(500);

  pinMode(kPinButton, INPUT);
  digitalWrite(kPinButton, HIGH);
}//--(end setup )---


DynamicJsonDocument doc(200);
int initPos[9];
bool hasInitPos = false;
int rotationSpeed = 350;
long currentMillis;

void loop() {  
  String payload;
  if (Serial.available() > 0) {
    payload = Serial.readStringUntil('\n');
    deserializeJson(doc, payload);
  }

  bool s1 = true;
  bool s2 = true;
  bool s3 = true;
  bool s4 = true;
  bool s5 = true;
  bool s6 = true;
  bool s7 = true;
  bool s8 = true;
  bool s9 = true;

  if (hasInitPos == false) {
    for (int index = 0; index < 9; index++) {
      initPos[index] = doc[String(index + 1)];
    }
    hasInitPos = true;
  }

  int pos[9];
  for (int index = 0; index < 9; index++) {
    pos[index] = doc[String(index + 1)];
  }

  if(digitalRead(kPinButton) == LOW) {
    for (int index = 0; index < 9; index++) {
      pos[index] = initPos[index];
    }
  }

  stepper1.moveTo(pos[0]);
  stepper1.setSpeed(rotationSpeed);
  stepper2.moveTo(pos[1]);
  stepper2.setSpeed(rotationSpeed);
  stepper3.moveTo(pos[2]);
  stepper3.setSpeed(rotationSpeed);
  stepper4.moveTo(pos[3]);
  stepper4.setSpeed(rotationSpeed);
  stepper5.moveTo(pos[4]);
  stepper5.setSpeed(rotationSpeed);
  stepper6.moveTo(pos[5]);
  stepper6.setSpeed(rotationSpeed);
  stepper7.moveTo(pos[6]);
  stepper7.setSpeed(rotationSpeed);
  stepper8.moveTo(pos[7]);
  stepper8.setSpeed(rotationSpeed);
  stepper9.moveTo(pos[8]);
  stepper9.setSpeed(rotationSpeed);
  currentMillis = millis();
  while (millis() - currentMillis < 700) {
    s1 = stepper1.runSpeedToPosition();
    s2 = stepper2.runSpeedToPosition();
    s3 = stepper3.runSpeedToPosition();
    s4 = stepper4.runSpeedToPosition();
    s5 = stepper5.runSpeedToPosition();
    s6 = stepper6.runSpeedToPosition();
    s7 = stepper7.runSpeedToPosition();
    s8 = stepper8.runSpeedToPosition();
    s9 = stepper9.runSpeedToPosition();
  }
  currentMillis = millis();
}
