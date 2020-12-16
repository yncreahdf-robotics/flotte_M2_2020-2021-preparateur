#include "ros/ros.h"

#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

#include <preparateur/Commande.h>
#include <preparateur/Init.h>
#include <preparateur/Stockage.h>

#include "MQTTClient.h"

#include <iostream>

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
  
  ros::init(argc, argv, "Brain1");
  ros::NodeHandle n;


  ros::ServiceClient clientDemDistrib1 = n.serviceClient<preparateur::Commande>("DGobelet/Demande");
  preparateur::Commande srvDemDistrib1;
  
  ros::ServiceClient clientDemTourn1 = n.serviceClient<preparateur::Commande>("Tourniquet/commande");
  preparateur::Commande srvDemTourn1;

  ros::ServiceClient clientDemStock1 = n.serviceClient<preparateur::Stockage>("/Stockage/Demande");
  preparateur::Stockage srvDemStock1;

  std_msgs::UInt16 msg_test;

  ros::Subscriber sub = n.subscribe("Supperviseur/Commande", 1000, supperviseurCallback);

  while (ros::ok())
  {
	

	switch(dem)
	{
		case 0:
			
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

				std::system("rosrun preparateur runGobN1.sh");
				srvDemTourn1.request.com = "100010";
				if (clientDemTourn1.call(srvDemTourn1)) //Demande du tourniquet
				{
				  	
				  
				}
				else
				{
				  ROS_ERROR("Failed to call service tourniquet");
				}

				std::system("rosrun preparateur runDeGobN1.sh");

				std::system("rosrun preparateur demo_Stock.sh");

			}





			if (clientDemStock1.call(srvDemStock1)) //Demande d'un contenant
			{
				ROS_INFO("Etat du stockage actuel");
			  	ROS_INFO("%s",srvDemStock1.response.stockage);
			  	
				
			  
			}
			else
			{
			  ROS_ERROR("Failed to call service stockage");
			}



			





			//Demande contenu

			dem=10;
			ros::spinOnce();
			break;
	
	}
  	ros::spinOnce();
  }
}
