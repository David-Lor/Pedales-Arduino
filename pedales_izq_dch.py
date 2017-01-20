#!/usr/bin/env python
import serial
import keyboard

ser = serial.Serial('/dev/ttyUSB0', 115200)
izq=False
dch=False
nad=False
prevIzq=False
prevDch=False

while 1:
    lectura = ser.readline()
    print(lectura)
    pos = lectura[:3]
    if pos == 'izq':
        print("Izquierda")
        izq=True
        dch=False
    elif pos == 'dch':
        print("Derecha")
        dch=True
        izq=False
    elif pos == 'nad':
        print("Nada")
        dch=False
        izq=False
        nad=True
    if izq and not prevIzq:
        keyboard.press('i')
    if dch and not prevDch:
        keyboard.press('d')
    if nad:
        if prevIzq:
            keyboard.release('i')
        if prevDch:
            keyboard.release('d')
    prevIzq=izq
    prevDch=dch
ser.close()
