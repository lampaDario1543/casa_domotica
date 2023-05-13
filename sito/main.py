import eel
import serial
import time as t
port="COM4" #This will be different for various devices and on windows it will probably be a COM port.
bluetooth=serial.Serial(port, 115200)#Start communications with the bluetooth unit
#port_in="COM6"
#bluetooth_in=serial.Serial(port_in, 115200)
t.sleep(5)
print("Connected")
eel.init("web")
@eel.expose
def cucina(accendi):
    data = "Accendi " if accendi else "Spegni "
    bluetooth.write(data.encode())
@eel.expose
def getTemperature():
    bluetooth.write("getTemp ".encode())
    data = bluetooth.readline().decode().strip()
    temp, hum = data.split(",")
    print(temp, hum)
    return [float(temp), float(hum)]
    #return 0,0
eel.start("index.html")