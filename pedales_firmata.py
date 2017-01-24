#!/usr/bin/env python
import pyfirmata
import keyboard

izq=False
dch=False
nad=False
prevIzq=False
prevDch=False

print("Iniciado script")
board = pyfirmata.Arduino("/dev/ttyUSB0")
print("conectado arduino")
it = pyfirmata.util.Iterator(board)
it.start()
print("iniciada interaccion")
board.analog[0].enable_reporting()
while True:
    try:
        v = board.analog[0].read()
        #print("\r"+str(v))
        if v > 0.07 and v < 0.09:
            print("Izquierda")
            izq=True
            dch=False
        elif v > 0.17 and v < 0.4:
            print("Derecha")
            dch=True
            izq=False
        elif v > 0.11 and v < 0.12:
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
    except KeyboardInterrupt:
        break
board.exit()
print("ADIOS!!! :v")
