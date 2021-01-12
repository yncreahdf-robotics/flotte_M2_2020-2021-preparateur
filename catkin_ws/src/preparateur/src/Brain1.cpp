#include "ros/ros.h"

#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Bool.h>

#include <std_srvs/Trigger.h>

#include <preparateur/Commande.h>
#include <preparateur/Init.h>
#include <preparateur/Stockage.h>

#include "MQTTClient.h"

#include <iostream>
#include <iterator>

using namespace std;

int dem = 10;
bool act = false;

bool state = false;

string cocktailComposition = "xxxxxx";
string test;

//Traitement des demandes superviseur 
void supperviseurCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("Message from supervisor: [%s]", msg->data.c_str());

  if(msg->data.c_str()[0] == 'C') //Demande de faire un cocktail
  {
  	ROS_INFO("Demande d'un cocktail");
	
	for(int i = 1; i<7; i++)
	{
		cocktailComposition[i-1] = msg->data.c_str()[i];
	}
	ROS_INFO("%s",cocktailComposition);

	dem = 1;
  }
  else if(msg->data.c_str()[0] == '0') //Demande de charger 
  {
	dem=0;
  }
  
}

bool statePreparateur(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res)
{
	res.success = state;

	return true;
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

  ros::ServiceClient clientDemStock2 = n.serviceClient<preparateur::Commande>("/Stockage/Position");
  preparateur::Commande srvDemStockPos;


  ros::ServiceServer serverStatepreparateur = n.advertiseService("/Preparateur/State",statePreparateur);


  std_msgs::UInt16 msg_test;

  ros::Subscriber sub = n.subscribe("Supperviseur/Commande", 1000, supperviseurCallback);

  ros::Publisher pub = n.advertise<std_msgs::String>("Preparateur/TalkSup",1000);
  std_msgs::String msg2;
  std::stringstream ss2;
  std_msgs::String msg;
  std::stringstream ss;
  ss << "Pr";
  ss2 << "Ch";

  while (ros::ok())
  {
	

	switch(dem)
	{
		case 0:
			ROS_INFO("Le serveur est la");

			ROS_INFO("Previent le sup que j ai servi le produit au serveur");
			
			ROS_INFO("Niryo3 depose le produit sur le robot");
			std::system("rosrun preparateur runDeStockDemo.sh");

			ros::Duration(5.0).sleep();

			ROS_INFO("Previent le sup que j ai servi le produit au serveur");
		
		
		
	
			//msg2.data = ss2.str();
	    	//pub.publish(msg2);

			srvDemStockPos.request.com = "1";




			if (clientDemStock2.call(srvDemStockPos)) 
			{
				ROS_INFO("Position 1 stock");
			  	
			
			  
			}
			else
			{
			  ROS_ERROR("Failed to call service stockage");
			}

			
		
			msg2.data = ss2.str();
            pub.publish(msg2);

			dem=10;
			ros::spinOnce();
			break;






		case 1:
			bool E1 = false;
			state = true;
			
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
			

			//E1 = true; //A ENLEVER
			
			if(E1)
			{
				//Mouvement Niryo1 
				ROS_INFO("Niryo1 prend le gobelet");
				std::system("rosrun preparateur runGobN1.sh");

				srvDemTourn1.request.com = cocktailComposition;
				
				
				if (clientDemTourn1.call(srvDemTourn1)) //Demande du tourniquet de faire le cocktail
				{
				  	ROS_INFO("Cocktail en cours");
				  
				}
				else
				{
				  ROS_ERROR("Failed to call service tourniquet");
				}

				ROS_INFO("Niryo1 depose le gobelet");
				std::system("rosrun preparateur runDeGobN1.sh");

				ROS_INFO("Niryo2 depose le gobelet dans le stockage");
				std::system("rosrun preparateur demo_Stock.sh");


				srvDemStockPos.request.com = "2";





				if (clientDemStock2.call(srvDemStockPos)) //Demande d'un contenant
				{
					ROS_INFO("Position 2 stock");
				  	
				
				  
				}
				else
				{
				  ROS_ERROR("Failed to call service stockage");
				}




				//On previent le superviseur que le produit est pret
				ROS_INFO("Previent le sup que le produit est pret");
			
				//ros::Duration(240.0).sleep();
				msg.data = ss.str();	

				
				pub.publish(msg);
				ROS_INFO("Preparation d'une commande");
				ROS_INFO("Distribution contenant");

				

				dem=10;

			}


			state = false;

			

			//Demande contenu

			dem=10;
			ros::spinOnce();

			break;
	



	
	}
  	ros::spinOnce();
  }
}
