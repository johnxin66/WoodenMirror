import PIL
from PIL import ImageGrab
from PIL import Image
from PIL import ImageOps
from PIL import ImageStat
import time
import serial
import json

arduinoSerial = serial.Serial("/dev/cu.usbmodem143301") #Create Serial port object called arduinoSerial
time.sleep(2) #wait for 2 secounds for the communication to get established

maxAngle = 40
stepsPerRev = 4096
maxSteps = stepsPerRev / 360 * maxAngle

def image2Data():
    originalImage = PIL.ImageGrab.grab((1200, 100, 2200, 1600))
    bnwImage = PIL.ImageOps.grayscale(originalImage)
    bnwImage.save("result.png")

    grads = {}
    cropHeight = round(1500 / 3 + 0.5)
    cropWidth = round(1000 / 3 + 0.5)
    tileCount = 1
    for top in range(0, 1500, cropHeight):
        for left in range(0, 1000, cropWidth):
            crop = bnwImage.crop((left, top, left + cropWidth, top + cropHeight))
            stat = PIL.ImageStat.Stat(crop)
            statAvg = stat.sum[0] / stat.count[0]
            angle = round(maxSteps - statAvg / 255 * maxSteps)
            grads[tileCount] = angle
            tileCount += 1
    #print(grads)
    return grads

isOn = True

while isOn:
    grads = image2Data()
    gradsJson = json.dumps(grads)
    arduinoSerial.write(gradsJson.encode('ascii'))
    #arduinoSerial.flush()
    time.sleep(0.5)
