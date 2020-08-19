#include <AccelStepper.h>
#include <Wire.h>
#define address 1

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
#define motorPin53  22         // IN3 on the ULN2003 driver 5
#define motorPin54  23        // IN4 on the ULN2003 driver 5
#define motorPin61  24         // IN1 on the ULN2003 driver 6
#define motorPin62  25         // IN2 on the ULN2003 driver 6
#define motorPin63  26         // IN3 on the ULN2003 driver 6
#define motorPin64  27        // IN4 on the ULN2003 driver 6
#define motorPin71  28         // IN1 on the ULN2003 driver 7
#define motorPin72  29         // IN2 on the ULN2003 driver 7
#define motorPin73  30         // IN3 on the ULN2003 driver 7
#define motorPin74  31        // IN4 on the ULN2003 driver 7
#define motorPin81  32         // IN1 on the ULN2003 driver 8
#define motorPin82  33         // IN2 on the ULN2003 driver 8
#define motorPin83  34         // IN3 on the ULN2003 driver 8
#define motorPin84  35        // IN4 on the ULN2003 driver 8
#define motorPin91  36         // IN1 on the ULN2003 driver 9
#define motorPin92  37         // IN2 on the ULN2003 driver 9
#define motorPin93  38         // IN3 on the ULN2003 driver 9
#define motorPin94  39        // IN4 on the ULN2003 driver 9
#define motorPin101  40         // IN1 on the ULN2003 driver 10
#define motorPin102  41         // IN2 on the ULN2003 driver 10
#define motorPin103  42         // IN3 on the ULN2003 driver 10
#define motorPin104  43        // IN4 on the ULN2003 driver 10
#define motorPin111  44         // IN1 on the ULN2003 driver 11
#define motorPin112  45         // IN2 on the ULN2003 driver 11
#define motorPin113  46         // IN3 on the ULN2003 driver 11
#define motorPin114  47        // IN4 on the ULN2003 driver 11
#define motorPin121  48         // IN1 on the ULN2003 driver 12
#define motorPin122  49         // IN2 on the ULN2003 driver 12
#define motorPin123  50         // IN3 on the ULN2003 driver 12
#define motorPin124  51        // IN4 on the ULN2003 driver 12
#define ledPin 52

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
AccelStepper stepper10(4, motorPin101, motorPin103, motorPin102, motorPin104);
AccelStepper stepper11(4, motorPin111, motorPin113, motorPin112, motorPin114);
AccelStepper stepper12(4, motorPin121, motorPin123, motorPin122, motorPin124);
 
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
  stepper10.setCurrentPosition(0);
  stepper10.setMaxSpeed(500);
  stepper11.setCurrentPosition(0);
  stepper11.setMaxSpeed(500);
  stepper12.setCurrentPosition(0);
  stepper12.setMaxSpeed(500);

  pinMode(kPinButton, INPUT);
  digitalWrite(kPinButton, HIGH);

  pinMode(ledPin, OUTPUT);

  Wire.begin(address);
  Wire.onReceive(espReceiveEvent);
}//--(end setup )---


int rotationSpeed = 350;
float maxAngle = 40;
float stepsPerRev = 4096;
float maxSteps = stepsPerRev / 360 * maxAngle;
char header;
char tail;
char startByte = char(-120);
char endByte = char(-121);
int pin[12];

int byte2Int() {
  int buf = int(Wire.read());
  int angle = round(maxSteps - buf / 255.0 * maxSteps);
  return angle;
}

int byte2IntRev() {
  int buf = int(Wire.read());
  int angle = -round(maxSteps - buf / 255.0 * maxSteps);
  return angle;
}

bool isTransSuccessful = true;

void espReceiveEvent(int count) {
  if (Wire.available() > 0) {
    header = Wire.read();
    Serial.print(String(header));
    Serial.print(String(startByte));
    if (header == startByte) {
      digitalWrite(ledPin, HIGH);
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[0] = byte2Int();
      }
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[1] = byte2Int();
      }
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[2] = byte2Int();
      }
      /*
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[3] = byte2Int();
      }
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[4] = byte2IntRev();
      }
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[5] = byte2Int();
        Serial.print(pin[5]);
      }
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[6] = byte2Int();
      }
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[7] = byte2Int();
      }
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[8] = byte2Int();
      }
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[9] = byte2Int();
      }
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[10] = byte2IntRev();
      }
      while (Wire.available() == 0) {}
      if (Wire.available() > 0) {
        pin[11] = byte2IntRev();
      }
      */
      while (Wire.available() == 0) {}
      if (Wire.available() >= 1) {
        tail = Wire.read();
        if (tail != endByte) {
          isTransSuccessful = false;
        } else {
          digitalWrite(ledPin, LOW);
        }
      }
      
      /*
      while (Wire.available() < 2) {}
      if (Wire.available() >= 2) {
        twoBytes2Int(1);
      }
      while (Wire.available() < 2) {}
      if (Wire.available() >= 2) {
        twoBytes2Int(2);
      }
      while (Wire.available() < 2) {}
      if (Wire.available() >= 2) {
        twoBytes2Int(3);
      }
      while (Wire.available() < 2) {}
      if (Wire.available() >= 2) {
        twoBytes2IntReverse(4);
      }
      while (Wire.available() < 2) {}
      if (Wire.available() >= 2) {
        twoBytes2Int(5);
      }
      while (Wire.available() < 2) {}
      if (Wire.available() >= 2) {
        twoBytes2Int(6);
      }
      while (Wire.available() < 2) {}
      if (Wire.available() >= 2) {
        twoBytes2Int(7);
      }
      while (Wire.available() < 2) {}
      if (Wire.available() >= 2) {
        twoBytes2Int(8);
      }
      while (Wire.available() == 0) {}
      if (Wire.available() >= 1) {
        tail = Wire.read();
        if (tail != endByte) {
          isTransSuccessful = false;
        } else {
          digitalWrite(ledPin, HIGH);
        }
      }
      */
    }
  }
}

void loop() {
  if(digitalRead(kPinButton) == LOW) {
    for (int index = 0; index < 12; index++) {
      pin[index] = 0;
    }
  }

  /*
  if (Serial.available() > 0) {
    header = Serial.read();
    if (header == char(-100)) {
      while (Serial.available() < 2) {}
      if (Serial.available() >= 2) {
        twoBytes2Int(0);
      }
      while (Serial.available() < 2) {}
      if (Serial.available() >= 2) {
        twoBytes2Int(1);
      }
      while (Serial.available() < 2) {}
      if (Serial.available() >= 2) {
        twoBytes2Int(2);
      }
      while (Serial.available() < 2) {}
      if (Serial.available() >= 2) {
        twoBytes2Int(3);
      }
      while (Serial.available() < 2) {}
      if (Serial.available() >= 2) {
        twoBytes2IntReverse(4);
      }
      while (Serial.available() < 2) {}
      if (Serial.available() >= 2) {
        twoBytes2Int(5);
      }
      while (Serial.available() < 2) {}
      if (Serial.available() >= 2) {
        twoBytes2Int(6);
      }
      while (Serial.available() < 2) {}
      if (Serial.available() >= 2) {
        twoBytes2Int(7);
      }
      while (Serial.available() < 2) {}
      if (Serial.available() >= 2) {
        twoBytes2Int(8);
      }
    }
  }
  
  
  if (Serial.available() > 0) {
    header = Serial.read();
    if (header == char(-1)) {
      while (Serial.available() == 0) {}
      if (Serial.available() > 0) {
        pin[0] = Serial.read();
      }
      while (Serial.available() == 0) {}
      if (Serial.available() > 0) {
        pin[1] = Serial.read();
      }
      while (Serial.available() == 0) {}
      if (Serial.available() > 0) {
        pin[2] = Serial.read();
      }
      while (Serial.available() == 0) {}
      if (Serial.available() > 0) {
        pin[3] = Serial.read();
      }
      while (Serial.available() == 0) {}
      if (Serial.available() > 0) {
        pin[4] = Serial.read();
      }
      while (Serial.available() == 0) {}
      if (Serial.available() > 0) {
        pin[5] = Serial.read();
      }
      while (Serial.available() == 0) {}
      if (Serial.available() > 0) {
        pin[6] = Serial.read();
      }
      while (Serial.available() == 0) {}
      if (Serial.available() > 0) {
        pin[7] = Serial.read();
      }
      while (Serial.available() == 0) {}
      if (Serial.available() > 0) {
        pin[8] = Serial.read();
      }
      //pin[0] = round(maxSteps - pin[0] / 255 * maxSteps);
    }
  }*/
  
  stepper1.moveTo(pin[0]);
  stepper1.setSpeed(rotationSpeed);
  stepper1.runSpeedToPosition();
  stepper2.moveTo(pin[1]);
  stepper2.setSpeed(rotationSpeed);
  stepper2.runSpeedToPosition();
  stepper3.moveTo(pin[2]);
  stepper3.setSpeed(rotationSpeed);
  stepper3.runSpeedToPosition();
  stepper4.moveTo(pin[3]);
  stepper4.setSpeed(rotationSpeed);
  stepper4.runSpeedToPosition();
  stepper5.moveTo(pin[4]);
  stepper5.setSpeed(rotationSpeed);
  stepper5.runSpeedToPosition();
  stepper6.moveTo(pin[5]);
  stepper6.setSpeed(rotationSpeed);
  stepper6.runSpeedToPosition();
  stepper7.moveTo(pin[6]);
  stepper7.setSpeed(rotationSpeed);
  stepper7.runSpeedToPosition();
  stepper8.moveTo(pin[7]);
  stepper8.setSpeed(rotationSpeed);
  stepper8.runSpeedToPosition();
  stepper9.moveTo(pin[8]);
  stepper9.setSpeed(rotationSpeed);
  stepper9.runSpeedToPosition();
  stepper10.moveTo(pin[9]);
  stepper10.setSpeed(rotationSpeed);
  stepper10.runSpeedToPosition();
  stepper11.moveTo(pin[10]);
  stepper11.setSpeed(rotationSpeed);
  stepper11.runSpeedToPosition();
  stepper12.moveTo(pin[11]);
  stepper12.setSpeed(rotationSpeed);
  stepper12.runSpeedToPosition();
}
