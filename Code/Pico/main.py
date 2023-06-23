# Imports
from machine import Pin, I2C
from ssd1306 import SSD1306_I2C
import time
import network   
import urequests

#Setting up wifi

ssid = 'TEB_Lawn'
password = '12345678'

def connect():
    #Connect to WLAN
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, password)
    while wlan.isconnected() == False:
        print('Waiting for connection...')
        display.fill(0) 
        display.text("Connecting ...",0,0)
        display.show()
        time.sleep(1)
    if wlan.isconnected() == True:
        display.fill(0) 
        display.text("Connected",0,0)
        display.show()
    print(wlan.ifconfig())




#Setting up the sreen
i2c=I2C(0,sda=Pin(0), scl=Pin(1), freq=400000)
time.sleep(1) 
display = SSD1306_I2C(128, 32, i2c)
display.fill(0) 

connect()

#Setting up the buttons
pin1 = Pin(5, Pin.IN, Pin.PULL_UP) # Left Button
pin2 = Pin(4, Pin.IN, Pin.PULL_UP) # Right Button
pin3 = Pin(3, Pin.IN, Pin.PULL_UP) # Brake Button
pin4 = Pin(2, Pin.IN, Pin.PULL_UP) # Center Button 


#Boot screen
display.show()

BrakeStat = 1
while True:
    if pin1.value()==0:
        print("Left Button Pressed")
        display.fill(0)
        display.text("TEB Mower",0,0)
        display.text('Left',0,12)
        try:
            r = urequests.head('http://192.168.4.1/Lefton')
            display.text("Sent",0,24)
            r.close()
        except:
            display.text("Failed",0,24)
        display.show()
        time.sleep(0.2)
        
    if pin2.value()==0:
        print("Right Button Pressed")
        display.fill(0)
        display.text("TEB Mower",0,0)
        display.text('Right',0,12)
        try:
            r = urequests.head('http://192.168.4.1/Righton')
            display.text("Sent",0,24)
            r.close()
        except:
            display.text("Failed",0,24)
        display.show()
        time.sleep(0.2)
        
        
    if pin3.value()==0:
        if BrakeStat == 1:
            print("Brake off")
            display.fill(0)
            display.text("TEB Mower",0,0)
            display.text('Brake off',0,12)
            try:
                r = urequests.head('http://192.168.4.1/Brakeoff')
                display.text("Sent",0,24)
                r.close()
            except:
                display.text("Failed",0,24)
            display.show()
            BrakeStat = 0
            time.sleep(0.2)
            
        elif BrakeStat == 0:
            display.fill(0)
            display.text("TEB Mower",0,0)
            display.text('Brake on',0,12)
            try:
                r = urequests.head('http://192.168.4.1/Brakeon')
                display.text("Sent",0,24)
                r.close()
            except:
                display.text("Failed",0,24)
            display.show()
            BrakeStat = 1
            time.sleep(0.2)
            
    
    if pin4.value()==0:
        start = time.time()
        time.sleep(0.2)
        while pin4.value()==0:
            time.sleep(0.01)
        length = time.time() - start
        if length < 0.3:
            print("Stopping truning")
            display.fill(0)
            display.text("TEB Mower",0,0)
            display.text('Stopping truning',0,12)
            try:
                r = urequests.head('http://192.168.4.1/Leftoff')
                display.text("Sent",0,24)
                r.close()
            except:
                display.text("Failed",0,24)
            display.show()
            time.sleep(0.2)
        else:
            print("Going Center")
            display.fill(0)
            display.text("TEB Mower",0,0)
            display.text('Center',0,12)
            try:
                r = urequests.head('http://192.168.4.1/cen')
                display.text("Sent",0,24)
                r.close()
            except:
                display.text("Failed",0,24)
            display.show()
            time.sleep(0.2)
            
            
