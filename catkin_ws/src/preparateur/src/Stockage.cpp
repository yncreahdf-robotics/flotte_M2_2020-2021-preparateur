#include "ros/ros.h"

#include <std_msgs/String.h>
#include <std_msgs/Int64.h>

#include "preparateur/Stockage.h"
#include "preparateur/Commande.h"

#include "preparateur/StockAjoutCom.h"
#include "preparateur/StockPositionCom.h"
#include "preparateur/StockPositionLibre.h"

#include <iostream>

using namespace std;


string etat = "00000000";
string idS[8] = {"x","x","x","x","x","x","x","x"};

bool sendStateFree(preparateur::StockPositionLibre::Request &req, preparateur::StockPositionLibre::Response &res)
{
	std::vector<double> vide ;
	int cpt = 0;

	for(int i = 0; i<8; i++)
	{

		//On regarde dans notre sotck les emplacements vides
		if(etat[i] == '0')
		{
			ROS_INFO("Emplacement %d vide", i);
			vide.push_back(i);	//Ajout de l'emplacement vide dans notre vecteur
			cpt++;
		}		

		
	}

	res.state = vide; //On envoie la réponse
	return true; 
}

bool addCom(preparateur::StockAjoutCom::Request &req, preparateur::StockAjoutCom::Response &res)
{
	string test = "aze";
	ROS_INFO("Ajout d'une commande %s a la position %d",req.idcom.c_str(),req.pos);

	etat[req.pos] = '1';
	idS[req.pos] = req.idcom.c_str();


	res.success = true;
	return true; 
}

bool delCom(preparateur::StockAjoutCom::Request &req, preparateur::StockAjoutCom::Response &res)
{
	string test = "aze";
	ROS_INFO("Suppresion de la commande %s a la position %d",req.idcom.c_str(),req.pos);

	etat[req.pos] = '0';
	idS[req.pos] = "";


	res.success = true;
	return true; 
}

bool searchCom(preparateur::StockPositionCom::Request &req, preparateur::StockPositionCom::Response &res)
{
	std::vector<double> comPosition ;	
	int cpt = 0;

	ROS_INFO("Recherche de la commande ",req.idcom.c_str());

	for(int i = 0; i < 8; i++)
	{
		if(req.idcom.c_str() == idS[i])
		{
			comPosition.push_back(i);
			cpt++;
			
		} 
	}

	if(cpt == 0)
	{
		ROS_ERROR("Il n existe pas de commande : %s",req.idcom.c_str());
		return false; 
	}
	else
	{	
		res.pos = comPosition;	
		return true;
	}
	
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "Stockage");
  ros::NodeHandle n;

  ros::ServiceServer stockService1 = n.advertiseService("/Stockage/Etat",sendStateFree);
  ros::ServiceServer stockService2 = n.advertiseService("/Stockage/AjoutCom",addCom);
  ros::ServiceServer stockService4 = n.advertiseService("/Stockage/SuppCom",delCom);
  ros::ServiceServer stockService3 = n.advertiseService("/Stockage/PositionCom",searchCom);

  ROS_INFO("Initialisation du stockage : ");
  ROS_INFO("%s", etat.c_str());

  while (ros::ok())
  {
	
  	ros::spinOnce();
  }
}
