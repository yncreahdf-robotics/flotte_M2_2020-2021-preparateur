#include "ros/ros.h"

#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

#include "test_serial_arduino/Connexion.h"
#include "test_serial_arduino/DemandeContenant.h"

#include "MQTTClient.h"

#include <iostream>

#include <wiringPi.h>

#define NIRYO_1 	2
#define NIRYO_1I 	3 //Mouvement niryo1 fini
using namespace std;

int dem = 10;
bool act = false;

void supperviseurCallback(const std_msgs::UInt16::ConstPtr& msg)
{
 

  ROS_INFO("Message from supervisor: [%d]", msg->data);
  if(msg->data == 0)
  {
	dem = 0;
    act = true;
  }
  else if(msg->data == 1)
  {
	dem = 1;
    act = true;
  }
  
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "prog2");
  ros::NodeHandle n;

 ros::ServiceClient clientCoDistrib1 = n.serviceClient<test_serial_arduino::Connexion>("co_distrib_contenant");
  test_serial_arduino::Connexion srvCoDistrib1;

  ros::ServiceClient clientDemDistrib1 = n.serviceClient<test_serial_arduino::DemandeContenant>("dem_distrib_contenant");
  test_serial_arduino::DemandeContenant srvDemDistrib1;
  
  ros::Publisher dis_pub = n.advertise<std_msgs::UInt16>("distrib_sub", 1000);

  std_msgs::UInt16 msg_test;

  ros::Subscriber sub = n.subscribe("infoSup", 1000, supperviseurCallback);

  setenv("WIRINGPI_GPIOMEM", "1", 1);
  wiringPiSetupGpio();
  pinMode(NIRYO_1, OUTPUT);
  pinMode(NIRYO_1I, INPUT);

  while (ros::ok())
  {


	switch(dem)
	{
		case 0:
			ROS_INFO("Test co");
		  	if (clientCoDistrib1.call(srvCoDistrib1))
			{
			  ROS_INFO("Alors success : %d", srvDemDistrib1.response.success);
			}
			else
			{
			  ROS_ERROR("Failed to call service connexion");
			}

			dem=10;
			ros::spinOnce();
			break;

		case 1:
			ROS_INFO("Preparation d'une commande");
			ROS_INFO("Distribution contenant");
			
			bool E1 = false;

		  	if (clientDemDistrib1.call(srvDemDistrib1)) //Demande d'un contenant
			{
			  	ROS_INFO("Rep : %I64d", srvDemDistrib1.response.code);
			  	
				switch(srvDemDistrib1.response.code)
				{
					case 1:
						ROS_ERROR("Obstacle present");
						E1 = false;
						break;
					case 2:
						ROS_ERROR("Contenant non present");
						E1 = false;
						break;
					case 3:
						ROS_INFO("Contenant present");
						E1 = true;
						break;
					case 4:
						ROS_ERROR("Plus de stock");
						E1 = false;
						break;
				}
			  
			}
			else
			{
			  ROS_ERROR("Failed to call service contenant");
			}

			if(E1)
			{
				//Mouvement Niryo1 
				
				do{
					digitalWrite(NIRYO_1, LOW);
				}while(digitalRead(NIRYO_1I) == false);
				digitalWrite(NIRYO_1, HIGH);
			}

			//Demande contenu

			dem=10;
			ros::spinOnce();
			break;
	
	}
  	ros::spinOnce();
  }
}
