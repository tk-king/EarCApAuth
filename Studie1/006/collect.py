import serial
import sys
with serial.Serial('/dev/ttyUSB3', 115200, timeout=1) as ser:
    with open(sys.argv[1], 'a') as file:
        while True:
            file.write(str(ser.readline()))   # read a '\n' terminated line
            file.write("\n")
            file.flush()
        
