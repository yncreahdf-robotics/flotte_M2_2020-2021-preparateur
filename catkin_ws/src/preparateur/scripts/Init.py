# -*- coding: utf-8 -*-

############################################################
### Programme principal à lancer pour démarrer le projet ###
############################################################


###############
### Imports ###
###############

# Import des fichiers .py propre au projet

#!/usr/bin/env python

#import FonctionsMQTT
import mysql.connector
import IPFinder
import paho.mqtt.client as mqtt

# Import des librairies exterieures au projet

import time
import threading
import math

import subprocess

from subprocess import call

##########################
### Variables globales ###
##########################

#	Robot retrieves his own IP
my_ip=IPFinder.get_my_ip()

#	TCP port used for MQTT
port = 1883


#	Determines the supervisor's IP using the hosts file
hosts = open('/etc/hosts','r')
for line in hosts:
	try:
		if line.split()[1] == "supIP":
			ipsuperviseur = line.split()[0]
	except IndexError:
		pass

###	ROBOTS VARIABLES     ###
type_robot="Caroita"
etat_robot="libre"

######################
### Initialisation ###
######################


############
### Defs ###
############

#!/usr/bin/env python3

def on_connect(client, userdata, flags, rc):

	print("Connected with result code "+str(rc))
	if rc==0:
		print("connection ok")
	else:
		print("connection no")


def on_disconnect(client, userdata, rc):

	print("Client Got Disconnected")


def on_message(client, userdata, msg):

	#print("Yes! i receive the message :" , str(msg.payload))
	#print("message received ", msg.payload.decode("utf-8"))
        #with open('data.json', 'w') as f:
        #json.dumps(msg.payload.decode("utf-8"))
	#print("message topic=",msg.topic)
	#print("message qos=",msg.qos)
	#print("message retain flag=",msg.retain)
	if (msg.topic=="Ordre/Envoi" and msg.payload.decode("utf-8").split("/")[0]==my_ip):
		global etat_robot		 
		etat_robot="occupe"		
		print("ORDRE REçU")
		
			
			#TODO insérer code robot avec pour destination la "pose" déterminée

		if (msg.payload.decode("utf-8").split("/")[1]=="Prepare"):
			boisson=msg.payload.decode("utf-8").split("/")[2]
			print("preparation de "+boisson)
			rc = call("./runAlgo.sh",shell=True)

		if (msg.topic=="Ping/Feedback" and msg.payload.decode("utf-8").split("/")[0]==my_ip):
			print("boucle feedback")
			if msg.payload.decode("utf-8").split("/")[1] == "No":
				print("boucle feedback no")
				publish(ipsuperviseur, port, "Initialisation/Envoi", my_ip+"/"+type_robot , 2)
			
		

#Appel d'une fonction qui permet de recevoir un message

def subscribe(ip, port, topic, qos):

	global client
	client = mqtt.Client()

	client.on_connect = on_connect
	client.on_message = on_message
	client.on_disconnect = on_disconnect
	client.connect(ip,port,60)
	client.subscribe(topic, qos)
	client.loop_start()
	print("subscribed to "+topic)


#Appel d'une fonction qui permet d'envoyer un message

def publish(ip, port, topic, message, qos):

	client2 = mqtt.Client()

	client2.connect(ip,port,60)
	client2.loop_start()
	client2.publish(topic, message, qos)
	print("message sent on "+topic)


def pingRobot():

	threading.Timer(10, pingRobot).start()

	print ("Envoi du ping")
	
	publish(ipsuperviseur, port, "Robot/Ping", my_ip, 2)


def send_etat():
	publish(ipsuperviseur,port,"Robot/Etat", my_ip+"/"+etat_robot,2)




###################################
###	PROGRAMME PRINCIPAL	###
###################################


###	CONNECTS TO DATABASE	###
flotte_db=mysql.connector.connect(
	host=ipsuperviseur,
	database='flotte_db',
	user='robot',
	password='robot'
)

global mycursor
mycursor=flotte_db.cursor()

pingRobot()

#	subscribe to Ordre/Envo - waits for orders
subscribe(ipsuperviseur, port, "Ordre/Envoi", 2)


while(1):
	time.sleep(10)
