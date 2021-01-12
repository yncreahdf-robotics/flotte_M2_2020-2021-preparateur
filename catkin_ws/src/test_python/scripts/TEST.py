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

from preparateur.srv import StockAjoutCom

###################################
###	PROGRAMME PRINCIPAL	###
###################################



rospy.init_node('talker', anonymous=True)
rate = rospy.Rate(10) # 10hz

print("wesh")

rospy.wait_for_service('Supperviseur/DemandeCharge')

try:
	print("Demande de charger envoye")
	chargeCom = rospy.ServiceProxy('Supperviseur/DemandeCharge', StockAjoutCom)
	resp = chargeCom("1",0)

except rospy.ServiceException as e:
	print("Ah bah ca marche po")
while(1):
	time.sleep(10)












