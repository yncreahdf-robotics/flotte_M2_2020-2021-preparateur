#!/usr/bin/env python

import paho.mqtt.client as mqtt
import paho.mqtt.subscribe as subscribe


import rospy
from std_msgs.msg import String
from std_msgs.msg import UInt64
from std_msgs.msg import UInt16
# Callbacks

def on_connect(client, userdata, flags, rc):

       	print("Connected with result code "+str(rc))
       	if rc==0:
       	        print("ok")
       	else:
       	        print("no")
       	client.subscribe("topic/DemoPreparateur", qos=0)



def on_disconnect(client, userdata, rc):

        print("Client Got Disconnected")

def on_message(client, userdata, msg):

       	print("Yes! i receive the message :" , str(msg.payload))
       	print("message received " ,str(msg.payload.decode("utf-8")))
       	print("message topic=",msg.topic)
       	print("message qos=",msg.qos)
       	print("message retain flag=",msg.retain)

	if str(msg.payload.decode("utf-8")) == "Dem":
		hello_str =1
		pub.publish(hello_str)
		rate.sleep()
		

if __name__ == '__main__':

	#pub = rospy.Publisher('infoSup', UInt64, queue_size=10)
	pub = rospy.Publisher('Supperviseur/Commande', UInt16, queue_size=10)
	rospy.init_node('talker', anonymous=True)
	rate = rospy.Rate(10) # 10hz

       	client = mqtt.Client()
       	#client.connect("192.168.43.197",1883,60)
	client.connect("192.168.1.9",1883,60)
       	client.on_connect = on_connect
       	client.on_message = on_message
       	client.on_disconnect = on_disconnect

       	client.loop_forever()



