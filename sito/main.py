import eel
import serial
import time as t
port="COM4" #This will be different for various devices and on windows it will probably be a COM port.
bluetooth=serial.Serial(port, 115200)#Start communications with the bluetooth unit
t.sleep(5)
print("Connected")
eel.init("web")
@eel.expose
def cucina(accendi):
    data = "Accendi " if accendi else "Spegni "
    bluetooth.write(data.encode())
    return 'Ciao'

eel.start("index.html")