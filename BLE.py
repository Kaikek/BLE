import time
import board
import adafruit_dht
import bluetooth

dht_device = adafruit_dht.DHT11(21)

def temp ():
    try:
        global temp
        global temperature
        temperature = dht_device.temperature
    except RuntimeError:
        time.sleep(2)

def connect ():
    bd_addr = "78:21:84:88:B3:E6"
    port = 1
    sock=bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    sock.connect((bd_addr, port))
    temp = str(f'{temperature}' + '*C')
    print(temp)
    sock.send(temp)
    sock.close()

if __name__ == "__main__":
    while True:
        temp()
        connect()
        time.sleep(5)