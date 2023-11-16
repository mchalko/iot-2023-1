from paho.mqtt import client as mqtt_client
import random

broker = '127.0.0.1'
port = 1883
id = f'python-mqtt-{random.randint(0, 1000)}'
messages = {}
client = None

def _on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)

def _on_message(client, userdata, msg):
    messages[msg.topic] = msg.payload.decode()    
        
def connect():
    global client
    client = mqtt_client.Client(client_id=id)
    
    client.on_connect = _on_connect
    client.on_message = _on_message
    client.connect(broker, port)
    client.subscribe("#")    
    client.loop_start()


def disconnect():
    client.disconnect()
    client.loop_stop(force=False)
