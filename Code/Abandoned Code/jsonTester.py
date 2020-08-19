import serial
import json
import time

data = {}
data[1] = 200
data[2] = 400
data[3] = 600

jsonData = json.dumps(data)
print(jsonData)
ser = serial.Serial("/dev/cu.usbmodem144301")
time.sleep(2);
ser.write(jsonData.encode('ascii'))
ser.flush()
