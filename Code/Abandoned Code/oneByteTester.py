import cv2
import numpy as np
import PIL
from PIL import Image
from PIL import ImageOps
from PIL import ImageStat
from PIL import ImageGrab
import time
import serial
import struct
import inspect

import pyscreenshot

#arduinoSerial = serial.Serial(port = "/dev/cu.usbmodem143301", baudrate = 115200) #Create Serial port object called arduinoSerial
time.sleep(2) #wait for 2 secounds for the communication to get established

maxAngle = 40
stepsPerRev = 4096
maxSteps = stepsPerRev / 360 * maxAngle

def pics2Data():
    """
    cap = cv2.VideoCapture(0)
    while(True):
        # Capture frame-by-frame
        ret, frame = cap.read()

        # Our operations on the frame come here
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Display the resulting frame
        cv2.imshow('frame', gray)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # When everything done, release the capture
    cap.release()
    cv2.destroyAllWindows()
    """
    timeStart = time.time()
    originalImage = PIL.ImageGrab.grab((1200, 100, 2200, 1600))
    timecapture = time.time()
    print(timecapture - timeStart)
    bnwImage = PIL.ImageOps.grayscale(originalImage) #capture gray
    timegray = time.time()
    crop = bnwImage.crop((0, 0, 100, 200))
    timecrop = time.time()
    #print(timegray - timecapture, timecrop - timegray)
    bnwImage.save("frame.png")
    
    grads = {}
    cropHeight = round(1500 / 3 + 0.5)
    cropWidth = round(1000 / 3 + 0.5)
    tileCount = 0
    timesf = time.time()
    for top in range(0, 1500, cropHeight):
        for left in range(0, 1000, cropWidth):
            crop = bnwImage.crop((left, top, left + 1, top + 1))
            #crop = bnwImage.crop((left, top, left + cropWidth, top + cropHeight))
            stat = PIL.ImageStat.Stat(crop)
            statAvg = round(stat.sum[0] / stat.count[0])
            angle = round(maxSteps - statAvg / 255 * maxSteps)
            grads[tileCount] = angle
            tileCount += 1
    timeend = time.time()
    #print(timeend - timesf)
    return grads

isOn = True
stepperOne = -1;

while isOn:
    #timeStart = time.time()
    grads = pics2Data()
    #timeGrads = time.time()
    #grads[4] = -grads[4]
    tail = -200
    header1 = -1
    #data1Byte = struct.pack('>9B', grads[0], grads[1], grads[2], grads[3], grads[4], grads[5], grads[6], grads[7], grads[8])
    #tailByte = struct.pack('>b', tail)
    header1Byte = struct.pack('>b', header1)
    #data2Byte = struct.pack('>B', data2)
    print(grads)
    #arduinoSerial.write(header1Byte)
    #arduinoSerial.write(data1Byte)
    #arduinoSerial.write(data2Byte)
    #arduinoSerial.flush()
    #timeEnd = time.time()
    #print(timeGrads - timeStart)
    #time.sleep(0.1)
