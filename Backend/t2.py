
import random
import json
import base64
import time
from datetime import datetime
import paho.mqtt.client as mqtt
from getTweet import *
MASTER_KILL_SWITCH=0

msgV=""
topicV=""
hastagValue='mars'

def on_connect(client, userdata, rc):
    #print("Connected with result code "+str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("twitter/hashtag_set")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    global dataFreq
    global msgV,topicV, hastagValue
    #print(msg.topic+" "+str(msg.payload))
    topicV=str(msg.topic)
    msgV=str((msg.payload).decode('utf-8'))

    if(topicV=='twitter/hashtag_set'):
        doSomethins=0
        hastagValue=msgV
        # client.publish('BLEMesh/API/response',str(k)+'^Done')
        
    
clientID_prefix=""
for i in range(0,6):
    clientID_prefix=clientID_prefix + str(random.randint(0,99999))


client = mqtt.Client("C1"+clientID_prefix)
#client.on_connect = on_connect
client.on_message = on_message

client.connect("broker.hivemq.com", 1883, 60)
client.subscribe("twitter/hashtag_set")


client.loop_start()
lastTweet=''
oldtime = time.time()
print(getTweet(hastagValue))
while 1:
    
    # lastTweet=getTweet()
    if time.time() - oldtime > 59:
        oldtime=time.time()
        nowTweet=getTweet(hastagValue)
        if(lastTweet!=nowTweet):
            lastTweet=nowTweet
        client.publish('twitter/tweet_get',lastTweet)
