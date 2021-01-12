#include "ros/ros.h"

#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Bool.h>

#include <std_srvs/Trigger.h>

#include <preparateur/Commande.h>
#include <preparateur/Init.h>
#include <preparateur/Stockage.h>

#include "preparateur/StockAjoutCom.h"
#include "preparateur/StockPositionCom.h"
#include "preparateur/StockPositionLibre.h"

#include "MQTTClient.h"

#include <iostream>
#include <sstream>
#include <iterator>

#include <string>

using namespace std;

int dem = 10;
bool act = false;

bool state = false;

string cocktailComposition = "xxxxxx";
string test;




  ros::ServiceClient clientDemDistrib1;
  preparateur::Commande srvDemDistrib1;
  
  ros::ServiceClient clientDemTourn1;
  preparateur::Commande srvDemTourn1;

  ros::ServiceClient clientDemStock1;
  preparateur::Stockage srvDemStock1;

  ros::ServiceClient clientDemStock2;
  preparateur::Commande srvDemStockPos;


  ros::ServiceServer serverStatepreparateur;



  ros::ServiceClient clientStockStateFree;
  preparateur::StockPositionLibre srvStockStateFree;


  ros::ServiceClient clientStockComPos;
  preparateur::StockPositionCom srvStockStockComPos;

  ros::ServiceClient clientStockState;
  preparateur::Init srvStockStockState;


  ros::ServiceClient clientStockDel;
  preparateur::StockAjoutCom srvDemStockDel;

  ros::ServiceClient clientStockAjout;
  preparateur::StockAjoutCom srvDemStockAjout;



  ros::ServiceClient clientStockPos;



  ros::ServiceServer demandeCom;

  int IDCOM = -1;


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


bool faireCom(preparateur::StockAjoutCom::Request &req, preparateur::StockAjoutCom::Response &res)
{
	ROS_INFO("Message from supervisor: [%s]", req.idcom.c_str());

  	if(req.idcom.c_str()[0] == 'C') //Demande de faire un cocktail
  	{
  		ROS_INFO("Demande d'un cocktail magique");
	
		for(int i = 1; i<7; i++)
		{
			cocktailComposition[i-1] = req.idcom.c_str()[i];
		}
		ROS_INFO("%s",cocktailComposition);



		ROS_INFO("ID COMMANDE : %d",req.pos);
		IDCOM = req.pos;
		dem = 1;
  	}
}

void niryoGoToPos(int pos)
{
	ROS_INFO("Demande mouvement niryo 2");
	pos = pos + 1;

	if (clientStockState.call(srvStockStockState)) 
	{
		ROS_INFO("Posiiton du stock %d",srvStockStockState.response.code);
		
	  	if(pos >= 5 && pos <= 8)
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
				case 5:
					ROS_INFO("Mouvement niryo2 vers position 5");
					std::system("rosrun preparateur runNiryo2_dP1.sh");
					break;
				case 6:
					ROS_INFO("Mouvement niryo3 vers position 6");
					std::system("rosrun preparateur runNiryo2_dP2.sh");
					break;
				case 7:
					ROS_INFO("Mouvement niryo3 vers position 7");
					std::system("rosrun preparateur runNiryo2_dP3.sh");
					break;
				case 8:
					ROS_INFO("Mouvement niryo3 vers position 8");
					std::system("rosrun preparateur runNiryo2_dP4.sh");
					break;
			}
		}


		if(pos >= 1 && pos <= 4)
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
				case 1:
					ROS_INFO("Mouvement niryo2 vers position 1");
					std::system("rosrun preparateur runNiryo2_dP1.sh");
					break;
				case 2:
					ROS_INFO("Mouvement niryo2 vers position 2");
					std::system("rosrun preparateur runNiryo2_dP2.sh");
					break;
				case 3:
					ROS_INFO("Mouvement niryo2 vers position 3");
					std::system("rosrun preparateur runNiryo2_dP3.sh");
					break;
				case 4:
					ROS_INFO("Mouvement niryo2 vers position 4");
					std::system("rosrun preparateur runNiryo2_dP4.sh");
					break;
			}
		}
	}
	else
	{
	  ROS_ERROR("Failed to call service stockage");
	}
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "Brain1");
  ros::NodeHandle n;

  
  clientDemDistrib1 = n.serviceClient<preparateur::Commande>("DGobelet/Demande");

  
  clientDemTourn1 = n.serviceClient<preparateur::Commande>("Tourniquet/commande");
  preparateur::Commande srvDemTourn1;

  clientDemStock1 = n.serviceClient<preparateur::Stockage>("/Stockage/Demande");
  preparateur::Stockage srvDemStock1;

  clientDemStock2 = n.serviceClient<preparateur::Commande>("/Stockage/Position");
  


  serverStatepreparateur = n.advertiseService("/Preparateur/State",statePreparateur);







  clientStockComPos = n.serviceClient<preparateur::StockPositionCom>("/Stockage/PositionCom");
  
  clientStockState = n.serviceClient<preparateur::Init>("/Stockage/Demande");  

  clientStockPos = n.serviceClient<preparateur::Commande>("/Stockage/Position");
  
  clientStockDel = n.serviceClient<preparateur::StockAjoutCom>("/Stockage/SuppCom");

  clientStockAjout = n.serviceClient<preparateur::StockAjoutCom>("/Stockage/AjoutCom");










  ros::ServiceClient clientStockStateFree;
  preparateur::StockPositionLibre srvStockStateFree;



  clientStockStateFree = n.serviceClient<preparateur::StockPositionLibre>("/Stockage/Etat");








  
  demandeCom= n.advertiseService("Supperviseur/DemandeCommande",faireCom);


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









				//On regarde les emplacement vide dans le stockage

				int pos;
				
				if (clientStockStateFree.call(srvStockStateFree)) 
				{
					ROS_INFO("Emplacement vide ");
				  	ROS_INFO("%f", srvStockStateFree.response.state[0]);
					
				    pos = srvStockStateFree.response.state[0];
				}
				else
				{
				  ROS_ERROR("Failed to call service stockage");
				}

				ROS_INFO("Demande au niryo de mettre la commande dans le stockage");

				niryoGoToPos(pos);

				//On ajoute la commande dans le stock

				std::ostringstream os;
				os << IDCOM;

				


				srvDemStockAjout.request.idcom = os.str();
				srvDemStockAjout.request.pos = pos;

				if (clientStockAjout.call(srvDemStockAjout)) 
				{
					ROS_INFO("Emplacement vide ");
				  	ROS_INFO("%f", srvStockStateFree.response.state[0]);
					
				    //pos = srvStockStateFree.response.state[0];
				}
				else
				{
				  ROS_ERROR("Failed to call service stockage");
				}




/*
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

*/


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
