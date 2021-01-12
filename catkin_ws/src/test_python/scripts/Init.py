#!/usr/bin/env python

import rospy
from std_msgs.msg import String

import mysql.connector
import paho.mqtt.client as mqtt

import IPFinder

import time
import threading
import math

import subprocess

import Commande
import Article

from subprocess import call

import rospy
from std_msgs.msg import String
from std_msgs.msg import UInt64
from std_msgs.msg import UInt16
from std_srvs.srv import Trigger

from preparateur.srv import Init

from preparateur.srv import StockAjoutCom

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

def on_connect(client, userdata, flags, rc):

	print("Connected with result code "+str(rc))
	if rc==0:
		print("connection ok")
	else:
		print("connection no")


def on_disconnect(client, userdata, rc):

	print("Client Got Disconnected")


def state_preprateur_client():
	rospy.wait_for_service('/Preparateur/State')
	try:
		state_preprateur = rospy.ServiceProxy('/Preparateur/State', Trigger)
		resp = state_preprateur()
		return resp.success
	except rospy.ServiceException as e:
		print("Service state preparateur n a pas fonctionne")

def on_message(client, userdata, msg):

	global flotte_db

	print("Yes! i receive the message :" , str(msg.payload))

	if (msg.topic=="Preparateur/Prepare" and msg.payload.decode("utf-8").split("/")[0]==my_ip):
		global etat_robot		 
		etat_robot="occupe"		
		print("ORDRE RECU")

		commandeID=msg.payload.decode("utf-8").split("/")[1] #numero de la table
		print("Demande preparation de la commande "+str(commandeID))
		
		print("Taille com " + str(len(Commande.get_Commande_with_status_and_commandNbr(flotte_db, commandeID, "Ordered"))))
		

		#for i in Commande.get_Commande_with_status_and_commandNbr(flotte_db, commandeID, "Ordered"): #Tant que la commande n est pas prete
			
			
		print("idProduit : ")
		print(Commande.get_Commande_with_status_and_commandNbr(flotte_db, commandeID, "Ordered")[0][0])

		if (state_preprateur_client() == False):
		
			print("Le preparateur est disponible pour faire la commande")
			tabCom = Commande.get_Bouteille(flotte_db, Commande.get_Commande_with_status_and_commandNbr(flotte_db, commandeID, "Ordered")[0][0])[0]
			print(tabCom)
		
			envoieCom = "C"

			#for c in range(5):
			#	envoieCom += str(tabCom[c])
		
			envoieCom += str(tabCom[0])
			envoieCom += str(tabCom[1])
			envoieCom += str(tabCom[2])
			envoieCom += str(tabCom[3])
			envoieCom += str(tabCom[4])
			envoieCom += str(tabCom[5])

			print(envoieCom)
	
			#pubSupCom.publish(envoieCom)

			try:
				print("Demande de commande envoye")
				faireCom = rospy.ServiceProxy('Supperviseur/DemandeCommande', StockAjoutCom)
				respFC = faireCom(envoieCom,int(commandeID))

			except rospy.ServiceException as e:
				print("Ah bah ca marche po")



			rate.sleep()
		else:
			print("Le preparateur n est pas disponnible pour faire la commande")
		#publish(ipsuperviseur,port,"Preparateur/Prepared", my_ip,2)
			
	if (msg.topic=="Preparateur/Charge" ):
				
		print("ORDRE RECU")
		print("demande preparateur depose produit !!!!!!!!!!!!!!!!!!")
		#hello_str ="0"
		#pubSupCom.publish(hello_str)
		#rate.sleep()
		commandeID=msg.payload.decode("utf-8").split("/")[1]
		try:
			print("Demande de charger envoye")
			chargeCom = rospy.ServiceProxy('Supperviseur/DemandeCharge', StockAjoutCom)
			respC = chargeCom(commandeID,0)

		except rospy.ServiceException as e:
			print("Ah bah ca marche po")


	if (msg.topic=="Ping/Feedback" and msg.payload.decode("utf-8").split("/")[0]==my_ip):
		if msg.payload.decode("utf-8").split("/")[1] == "No":

			print("reboot de la co mysql")
			publish(ipsuperviseur, port, "Initialisation/Envoi", my_ip + "/" + type_robot, 2)

			flotte_db=mysql.connector.connect(
				host=ipsuperviseur,
				database='flotte_db',
				user='robot',
				password='robot'
			)



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

def callback(data):
	rospy.loginfo("Message du preparateur %s", data.data)
	if data.data == "Pr":
			publish(ipsuperviseur,port,"Preparateur/Prepared", my_ip,2)
	if data.data == "Ch":
			publish(ipsuperviseur,port,"Preparateur/Charged", my_ip,2)


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


pingRobot()

publish(ipsuperviseur, port, "Initialisation/Envoi", my_ip + "/" + type_robot, 2)

#	subscribe to Ordre/Envo - waits for orders
subscribe(ipsuperviseur, port, "Preparateur/#", 2)
subscribe(ipsuperviseur, port, "Ping/Feedback", 2)

pubSupCom = rospy.Publisher('Supperviseur/Commande', String, queue_size=10)
pubSupServ = rospy.Publisher('Supperviseur/Serveur', String, queue_size=10)
rospy.init_node('talker', anonymous=True)
rate = rospy.Rate(10) # 10hz
rospy.Subscriber("Preparateur/TalkSup", String, callback)

rospy.wait_for_service('Supperviseur/DemandeCharge')


while(1):
	time.sleep(10)












