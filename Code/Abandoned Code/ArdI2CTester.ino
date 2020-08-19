#include <Wire.h>
#define I2CAddressESPWifi 0x06

void setup() {
  Serial.begin(115200);
  Wire.begin(I2CAddressESPWifi);
  Wire.onReceive(espWifiReceiveEvent);
}

void espWifiReceiveEvent(int count) {
  while (Wire.available() > 0) {
    Serial.print("Something's got here");
    char c = Wire.read();
    Serial.print(c);
  }
}

void loop() {
  delay(1);
}
