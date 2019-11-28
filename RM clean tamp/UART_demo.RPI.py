from Tkinter import *
import serial
import tkFont
import RPi.GPIO as GPIO
ser = serial.Serial('/dev/ttyUSB0')
win = Tk()
myFont = tkFont.Font(family = 'Helvetica', size = 36, weight = 'bold')
win.title("RM UART DEMO")
win.geometry('800x480')
writeto = '0000000'

def TRIGCH1():
    print("CH1 TRIGGERED")
    global writeto
    if writeto[0] == '0':
        writeto = '1' + writeto[1:4]
    else:
        writeto = '0' + writeto[1:4]
    print(writeto)
    ser.write(writeto)
def TRIGCH2():
    print("CH2 TRIGGERED")
    global writeto
    if writeto[1] == '0':
        writeto = writeto[0] + '1' + writeto[2:4]
    else:
        writeto = writeto[0] + '0' + writeto[2:4]
    print(writeto)
    ser.write(writeto)
def TRIGCH3():
    print("CH3 TRIGGERED")
    global writeto
    if writeto[2] == '0':
        writeto = writeto[0:2] + '1' + writeto[3]
    else:
        writeto = writeto[0:2] + '0' + writeto[3]
    print(writeto)
    ser.write(writeto)
def TRIGCH4():
    print("CH4 TRIGGERED")
    global writeto
    if writeto[3] == '0':
        writeto = writeto[0:3] + '1'
    else:
        writeto = writeto[0:3] + '0'
    print(writeto)
    ser.write(writeto)
    
    
    
print(ser.name)   
print(writeto)
CH1  = Button(win, text = "CH1", font = myFont, command = TRIGCH1, height =1 , width = 3) 
CH1.pack()

CH2 = Button(win, text = "CH2", font = myFont, command = TRIGCH2, height = 1, width =3 )
CH2.pack()

CH3  = Button(win, text = "CH3", font = myFont, command = TRIGCH3, height =1 , width = 3) 
CH3.pack()

CH4 = Button(win, text = "CH4", font = myFont, command = TRIGCH4, height = 1, width =3 )
CH4.pack()

mainloop()