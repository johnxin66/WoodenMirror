#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define FREQUENCY 50

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(&Wire, 0x47);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(&Wire, 0x45);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(&Wire, 0x41);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(&Wire, 0x42);
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver(&Wire, 0x40);

void setup() {
  Serial.begin(115200);
  pwm1.begin();
  pwm1.setPWMFreq(FREQUENCY);  // Analog servos run at ~50 Hz updates
  pwm2.begin();
  pwm2.setPWMFreq(FREQUENCY);
  pwm3.begin();
  pwm3.setPWMFreq(FREQUENCY);  // Analog servos run at ~50 Hz updates
  pwm4.begin();
  pwm4.setPWMFreq(FREQUENCY);
  pwm5.begin();
  pwm5.setPWMFreq(FREQUENCY);
  Wire.setClock(400000);
  yield();
}

/*int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}
*/
int pulseWidth(int angle) {
  int analogAngle = int(map(angle, 0, 45, 200, 300));
  return analogAngle;
}

int header;
int startByte = 126;
int endByte = 127;
int slaveNum;
byte dataBuffer[16];
void serialReceive() {
  if (Serial.available() > 0) {
    header = Serial.read();
    if (header == startByte) {
      while (Serial.available() == 0) {}
      if (Serial.available() >= 1) {
        slaveNum = int(Serial.read());
      }
      Serial.readBytesUntil(endByte, dataBuffer, 17);
      writeServo(dataBuffer, slaveNum);
    }
  }
}

void writeServo(byte servoAngles[], int boardNum) {
  for (int index = 0; index < 16; index++) {
    if (boardNum == 1) {
      pwm1.setPWM(index, 0, pulseWidth(servoAngles[index]));
    } else if (boardNum == 2) {
      pwm2.setPWM(index, 0, pulseWidth(servoAngles[index]));
    } else if (boardNum == 3) {
      pwm3.setPWM(index, 0, pulseWidth(servoAngles[index]));
    } else if (boardNum == 4) {
      pwm4.setPWM(index, 0, pulseWidth(servoAngles[index]));
    } else if (boardNum == 5) {
      pwm5.setPWM(index, 0, pulseWidth(servoAngles[index]));
    }
  }
}

void loop() {
  serialReceive();
}
