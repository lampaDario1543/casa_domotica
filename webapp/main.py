import eel
import serial
import time as t
port="COM6" #This will be different for various devices and on windows it will probably be a COM port.
bluetooth=serial.Serial(port, 115200)#Start communications with the bluetooth unit
t.sleep(5)
print("Connected")
eel.init("web")
@eel.expose
def setStatus(s):
    data=s+" "
    bluetooth.write(data.encode())
@eel.expose
def getTemperature():
    bluetooth.write("getTemp ".encode())
    data = bluetooth.readline().decode().strip()
    temp, hum = data.split(",")
    print(temp, hum)
    return [float(temp), float(hum)]
eel.start("index.html")