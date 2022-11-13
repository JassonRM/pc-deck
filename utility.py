import keyboard
import serial

port = "COM3"
baudrate = 9600

device = serial.Serial(port, baudrate, timeout=1)

while True:
    input = device.readline().decode("utf-8")
    if (input):
        code = int(input)
        if (code == 1):
            keyboard.press_and_release("ctrl+c")
        elif (code == 2):
            keyboard.press_and_release("ctrl+v")