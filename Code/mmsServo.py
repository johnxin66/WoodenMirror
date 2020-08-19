import cv2
import numpy as np
import PIL
from PIL import Image
from PIL import ImageOps
from PIL import ImageStat
from PIL import ImageGrab
import time
import serial
import mss
import struct

import pyscreenshot

upperArd = serial.Serial(port = "/dev/cu.usbmodem143401", baudrate = 115200)
middleArd = serial.Serial(port = "/dev/cu.usbmodem143301", baudrate = 115200)
lowerArd = serial.Serial(port = "/dev/cu.usbmodem14401", baudrate = 115200)
time.sleep(2) #wait for 2 secounds for the communication to get established

maxAngle = 40
frameHeight = 500
frameWidth = 300
tilesHeight = 20
tilesWidth = 12
cropHeight = round(1000 / tilesHeight + 0.5)
cropWidth = round(600 / tilesWidth + 0.5)

def pics2Data():
    # Part of the screen to capture
    with mss.mss() as sct:
        monitor = {"top": 60, "left": 700, "width": frameWidth, "height": frameHeight}
        sct_img = sct.grab(monitor)
        img_np = np.array(sct_img)
        bnwImage = np.reshape(cv2.cvtColor(img_np, cv2.COLOR_BGRA2GRAY), (1000, 600))
        #print(bnwImage[0:2, :])
        #print(len(bnwImage))

    angles = []
    tileCount = 0
    for top in range(0, 1000, cropHeight):
        for left in range(0, 600, cropWidth):
            crop = bnwImage[top:(top + cropHeight), left:(left + cropWidth)]
            '''
            print(crop)
            print(len(crop))
            print(len(crop[0]))
            '''
            stat = np.sum(crop)
            pixelCount = np.shape(crop)[0] * np.shape(crop)[1]
            statAvg = int(round(stat / pixelCount))
            angle = int(round(statAvg / 255 * maxAngle))
            angles += [maxAngle - angle]
            tileCount += 1               
    print("success")
    return angles

isOn = True
stepperOne = -1
startHeader = 126
tail = 127
headerByte = struct.pack('>b', startHeader)
tailByte = struct.pack('>b', tail)
numPCAs = 5
numArds = 3

def tester(index):
    grads = []
    for i in range(0, 240):
        grads += [0]
    grads[index] = 60
    return grads

while isOn:
    grads = pics2Data()
    '''
    for i in range(0, 240):
        grads = tester(i)
        time.sleep(0.2)
    '''
    upperGrads = grads[0:(16 * numPCAs)]
    middleGrads = grads[(16 * numPCAs):(16 * numPCAs * 2)]
    lowerGrads = grads[(16 * numPCAs * 2):(16 * numPCAs * 3)]
    
    for ard in range(0, numArds):
        for index in range(0, numPCAs):
            address = int(index + 1)
            addressByte = struct.pack('>B', address)
            i = index * 16
            if ard == 0:
                dataByte = struct.pack('>16B', upperGrads[i], upperGrads[i+1], upperGrads[i+2], upperGrads[i+3], upperGrads[i+4], upperGrads[i+5], upperGrads[i+6], upperGrads[i+7], upperGrads[i+8], upperGrads[i+9], upperGrads[i+10], upperGrads[i+11], upperGrads[i+12], upperGrads[i+13], upperGrads[i+14], upperGrads[i+15])
                upperArd.write(headerByte)
                upperArd.write(addressByte)
                upperArd.write(dataByte)
                upperArd.write(tailByte)
                upperArd.flush()
            elif ard == 1:
                dataByte = struct.pack('>16B', middleGrads[i], middleGrads[i+1], middleGrads[i+2], middleGrads[i+3], middleGrads[i+4], middleGrads[i+5], middleGrads[i+6], middleGrads[i+7], middleGrads[i+8], middleGrads[i+9], middleGrads[i+10], middleGrads[i+11], middleGrads[i+12], middleGrads[i+13], middleGrads[i+14], middleGrads[i+15])
                middleArd.write(headerByte)
                middleArd.write(addressByte)
                middleArd.write(dataByte)
                middleArd.write(tailByte)
                middleArd.flush()
            elif ard == 2:
                dataByte = struct.pack('>16B', lowerGrads[i], lowerGrads[i+1], lowerGrads[i+2], lowerGrads[i+3], lowerGrads[i+4], lowerGrads[i+5], lowerGrads[i+6], lowerGrads[i+7], lowerGrads[i+8], lowerGrads[i+9], lowerGrads[i+10], lowerGrads[i+11], lowerGrads[i+12], lowerGrads[i+13], lowerGrads[i+14], lowerGrads[i+15])
                lowerArd.write(headerByte)
                lowerArd.write(addressByte)
                lowerArd.write(dataByte)
                lowerArd.write(tailByte)
                lowerArd.flush()

     
