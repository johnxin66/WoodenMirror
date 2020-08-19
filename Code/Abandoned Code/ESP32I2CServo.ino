#include <Wire.h>
#define ledpin 14

void setup() {
  Wire.begin(21,22); //Change to Wire.begin() for non ESP.
  Serial.begin(115200);
  pinMode(ledpin, OUTPUT);
}

char header;
char startByte = char(-100);
char endByte = char(-101);
byte dataBuffer[12];
byte tempDataBuffer[3];
int slaveNum;

void transmitData(byte data4Transmission[], int address, int dataSize) {
  char transmissionHeader = char(-120);
  char transmissionTail = char(-121);
  Wire.beginTransmission(address);
  digitalWrite(ledpin, HIGH);
  Wire.write(transmissionHeader);
  Wire.write(data4Transmission, dataSize);
  Wire.write(transmissionTail);
  byte error = Wire.endTransmission();
  
  digitalWrite(ledpin, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    header = Serial.read();
    if (header == startByte) {
      while (Serial.available() == 0) {}
      if (Serial.available() >= 1) {
        slaveNum = int(Serial.read());
      }
      Serial.readBytesUntil(endByte, tempDataBuffer, 15);
      transmitData(tempDataBuffer, slaveNum, 3);
      /*
      if (slaveNum == 1) {
        Serial.readBytesUntil(endByte, dataBuffer, 15);
        transmitData(dataBuffer, slaveNum, 12);
      } else if (slaveNum == 2) {
        Serial.readBytesUntil(endByte, tempDataBuffer, 15);
        transmitData(tempDataBuffer, slaveNum, 4);
      }
      */
    }
  }
}
