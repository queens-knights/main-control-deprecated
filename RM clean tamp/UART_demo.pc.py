from tkinter import *
import serial
import tkinter.font

ser = serial.Serial('COM3')
win = Tk()
win.title("RM UART DEMO")
win.geometry('30x120')
writeto = '0000000'

def TRIGCH1():
    print("CH1 TRIGGERED")
    global writeto
    if writeto[0] == '0':
        writeto = '1' + writeto[1:4]
    else:
        writeto = '0' + writeto[1:4]
    print(writeto)
    ser.write(str.encode(writeto))
def TRIGCH2():
    print("CH2 TRIGGERED")
    global writeto
    if writeto[1] == '0':
        writeto = writeto[0] + '1' + writeto[2:4]
    else:
        writeto = writeto[0] + '0' + writeto[2:4]
    print(writeto)
    ser.write(str.encode(writeto))
def TRIGCH3():
    print("CH3 TRIGGERED")
    global writeto
    if writeto[2] == '0':
        writeto = writeto[0:2] + '1' + writeto[3]
    else:
        writeto = writeto[0:2] + '0' + writeto[3]
    print(writeto)
    ser.write(str.encode(writeto))
def TRIGCH4():
    print("CH4 TRIGGERED")
    global writeto
    if writeto[3] == '0':
        writeto = writeto[0:3] + '1'
    else:
        writeto = writeto[0:3] + '0'
    print(writeto)
    ser.write(str.encode(writeto))
    
    
    
print(ser.name)   
print(writeto)
CH1  = Button(win, text = "CH1",  command = TRIGCH1, height =1 , width = 3) 
CH1.pack()

CH2 = Button(win, text = "CH2", command = TRIGCH2, height = 1, width =3 )
CH2.pack()

CH3  = Button(win, text = "CH3", command = TRIGCH3, height =1 , width = 3) 
CH3.pack()

CH4 = Button(win, text = "CH4",  command = TRIGCH4, height = 1, width =3 )
CH4.pack()

mainloop()
