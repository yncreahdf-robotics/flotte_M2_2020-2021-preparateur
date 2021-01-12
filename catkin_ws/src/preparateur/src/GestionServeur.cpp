#include "ros/ros.h"

#include <std_msgs/String.h>
#include <std_msgs/Int64.h>
#include <std_msgs/Float64.h>

#include "preparateur/Stockage.h"
#include "preparateur/Commande.h"
#include "preparateur/Init.h"

#include "preparateur/StockPositionCom.h"
#include "preparateur/StockAjoutCom.h"

#include <iostream>
#include <vector>

using namespace std;

  

  ros::ServiceClient clientStockComPos;
  preparateur::StockPositionCom srvStockStockComPos;

  ros::ServiceClient clientStockState;
  preparateur::Init srvStockStockState;

  ros::ServiceClient clientStockPos;
  preparateur::Commande srvDemStockPos;

  ros::ServiceClient clientStockDel;
  preparateur::StockAjoutCom srvDemStockDel;

bool order = false;

void niryoGoToPos(int pos)
{

	if (clientStockState.call(srvStockStockState)) //Demande d'un contenant
	{
		ROS_INFO("Posiiton du stock %d",srvStockStockState.response.code);
		
	  	if(pos >= 5 && pos <= 8)
		{
			if(srvStockStockState.response.code == 2)
			{
				//Stockage pas dans la bonne position
				srvDemStockPos.request.com = "1";

				if (clientStockPos.call(srvDemStockPos)) //Demande d'un contenant
				{
					ROS_INFO("Position 1 stock");				  	
				}
				else
				{
				  ROS_ERROR("Failed to call service stockage");
				}
			}

			switch(pos){
				case 5:
					ROS_INFO("Mouvement niryo4 vers position 1");
					std::system("rosrun preparateur runNiryo4_Ext.sh");
					break;
				case 6:
					ROS_INFO("Mouvement niryo4 vers position 2");
					std::system("rosrun preparateur runNiryo4_Int.sh");
					break;
				case 7:
					ROS_INFO("Mouvement niryo5 vers position 2");
					std::system("rosrun preparateur runNiryo3_Int.sh");
					break;
				case 8:
					ROS_INFO("Mouvement niryo5 vers position 1");
					std::system("rosrun preparateur runNiryo3_Ext.sh");
					break;
			}
		}


		if(pos >= 1 && pos <= 4)
		{
			if(srvStockStockState.response.code == 1)
			{
				//Stockage pas dans la bonne position
				srvDemStockPos.request.com = "2";

				if (clientStockPos.call(srvDemStockPos)) //Demande d'un contenant
				{
					ROS_INFO("Position 2 stock");				  	
				}
				else
				{
				  ROS_ERROR("Failed to call service stockage");
				}
			}

			switch(pos){
				case 1:
					ROS_INFO("Mouvement niryo4 vers position 1");
					std::system("rosrun preparateur runNiryo4_Ext.sh");
					break;
				case 2:
					ROS_INFO("Mouvement niryo4 vers position 2");
					std::system("rosrun preparateur runNiryo4_Int.sh");
					break;
				case 3:
					ROS_INFO("Mouvement niryo5 vers position 2");
					std::system("rosrun preparateur runNiryo3_Int.sh");
					break;
				case 4:
					ROS_INFO("Mouvement niryo5 vers position 1");
					std::system("rosrun preparateur runNiryo3_Ext.sh");
					break;
			}
		}
	}
	else
	{
	  ROS_ERROR("Failed to call service stockage");
	}
}



void supperviseurCallback(const std_msgs::String::ConstPtr& msg)
{
 

	ROS_INFO("Message from supervisor ID COM: [%s]", msg->data.c_str());
	  
	srvStockStockComPos.request.idcom = msg->data.c_str();

	if (clientStockComPos.call(srvStockStockComPos)) //Demande d'un contenant
	{
		ROS_INFO("nb pos : %d",srvStockStockComPos.response.pos.size());
		ROS_INFO("Position(s) : ");

		ROS_INFO("%f ",srvStockStockComPos.response.pos[0]);

		niryoGoToPos(int(srvStockStockComPos.response.pos[0])+1);


		srvDemStockDel.request.pos = srvStockStockComPos.response.pos[0];
		srvDemStockDel.request.idcom = msg->data;

		if (clientStockDel.call(srvDemStockDel)) //On supprime du stock la commande qui vient d'être servie
		{
				
		}
		else
		{
		  ROS_ERROR("Failed to call service Del Stockage");
		}







		/*
		for(int i = 0; i < srvStockStockComPos.response.pos.size(); i++)
		{
			ROS_INFO("%f ",srvStockStockComPos.response.pos[i]);
			niryoGoToPos(int(srvStockStockComPos.response.pos[i])+1);


			srvDemStockDel.request.pos = srvStockStockComPos.response.pos[i];
			srvDemStockDel.request.idcom = msg->data;

			if (clientStockDel.call(srvDemStockDel)) //On supprime du stock la commande qui vient d'être servie
			{
					
			}
			else
			{
			  ROS_ERROR("Failed to call service Del Stockage");
			}

		}
	  	*/




	  //On previent le superviseur que la commande est sur le serveur

	  order = true;

	}
	else
	{
	  ROS_ERROR("Failed to call service stockage");
	}
  
}













bool chargeCom(preparateur::StockAjoutCom::Request &req, preparateur::StockAjoutCom::Response &res)
{
	ROS_INFO("Demande de charger une commande");
	ROS_INFO("id : %s",req.idcom.c_str());

	srvStockStockComPos.request.idcom = req.idcom.c_str();

	if (clientStockComPos.call(srvStockStockComPos)) //Demande d'un contenant
	{
		ROS_INFO("nb pos : %d",srvStockStockComPos.response.pos.size());
		ROS_INFO("Position(s) : ");

		ROS_INFO("%f ",srvStockStockComPos.response.pos[0]);

		niryoGoToPos(int(srvStockStockComPos.response.pos[0])+1);


		srvDemStockDel.request.pos = srvStockStockComPos.response.pos[0];
		srvDemStockDel.request.idcom = req.idcom.c_str();

		if (clientStockDel.call(srvDemStockDel)) //On supprime du stock la commande qui vient d'être servie
		{
				
		}
		else
		{
		  ROS_ERROR("Failed to call service Del Stockage");
		}

	  //On previent le superviseur que la commande est sur le serveur

	  order = true;

	}
	else
	{
	  ROS_ERROR("Failed to call service stockage");
	}
	


	return true; 
}















int main(int argc, char **argv)
{
  ros::init(argc, argv, "GestionServeur");
  ros::NodeHandle n;
  
  clientStockComPos = n.serviceClient<preparateur::StockPositionCom>("/Stockage/PositionCom");
  
  clientStockState = n.serviceClient<preparateur::Init>("/Stockage/Demande");  

  clientStockPos = n.serviceClient<preparateur::Commande>("/Stockage/Position");
  
  clientStockDel = n.serviceClient<preparateur::StockAjoutCom>("/Stockage/SuppCom");



  ros::ServiceServer demandeCharge = n.advertiseService("Supperviseur/DemandeCharge",chargeCom);








  ros::Subscriber sub = n.subscribe("Supperviseur/Serveur", 1000, supperviseurCallback);

  ros::Publisher pub = n.advertise<std_msgs::String>("Preparateur/TalkSup",1000);
  
  std_msgs::String msg2;
  std::stringstream ss2;
  ss2 << "Ch";

  msg2.data = ss2.str();
      

  ROS_INFO("Gestion des serveurs pret");


  while (ros::ok())
  {
	if(order)
	{
		pub.publish(msg2);
		order = false;
	}
  	ros::spinOnce();
  }
}
