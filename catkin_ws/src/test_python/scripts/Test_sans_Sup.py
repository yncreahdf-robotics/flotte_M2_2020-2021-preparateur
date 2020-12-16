#!/usr/bin/env python

import rospy
from std_msgs.msg import String



def test():
	
	testCompCocktail=[0]*6

	testCompCocktail[0]=2
	testCompCocktail[1]=0
	testCompCocktail[2]=1
	testCompCocktail[3]=0
	testCompCocktail[4]=0
	testCompCocktail[5]=0
	print(testCompCocktail)

	envoieCom = "C"

	for c in range(6):
		envoieCom += str(testCompCocktail[c])

	print(envoieCom)

	pubSupCom = rospy.Publisher('Supperviseur/Commande', String, queue_size=10)
	rospy.init_node('talker', anonymous=True)
	rate = rospy.Rate(10) # 10hz

	while not rospy.is_shutdown():
		pubSupCom.publish(envoieCom)
		rate.sleep()

test()















