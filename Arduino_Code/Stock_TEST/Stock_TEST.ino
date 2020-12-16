#include <ros.h>
#include <preparateur/Stockage.h>
#include <std_msgs/Int64.h>

//long stockage;
String stockage;
ros::NodeHandle  nh;

using preparateur::Stockage;



void initTab()
{
  
  if(analogRead(A0) > 100)
  {
    stockage = "1";
  }
  else
  {
    stockage  = "0" ;
  }
 
  if(analogRead(A1) > 100)
  {
    stockage = "1" + stockage;
  }
  else
  {
    stockage = "0" + stockage;
  } 
    
  if(analogRead(A2) > 100)
  {
    stockage = "1" + stockage;
  }
  else
  {
    stockage = "0" + stockage;
  } 
  
  if(analogRead(A3) > 100)
  {
    stockage = "1" + stockage;
  }
  else
  {
    stockage = "0" + stockage;
  } 

  
  if(analogRead(A4) > 100)
  {
    stockage = "1" + stockage;
  }
  else
  {
    stockage = "0" + stockage;
  } 
  
  
  if(analogRead(A5) > 100)
  {
    stockage = "1" + stockage;
  }
  else
  {
    stockage = "0" + stockage;
  }  
}

void callbackSto(const Stockage::Request & req, Stockage::Response & res){
  initTab();
  
  //Réception d'une demande
  nh.loginfo("Demande reçu : ");
  
  nh.loginfo("  Renvoie de l'etat du stock");
  nh.loginfo(stockage.c_str());
  res.stockage = stockage.c_str();  
  res.success = true;
  
}

ros::ServiceServer<Stockage::Request, Stockage::Response> server1("/Stockage/Demande",&callbackSto);

void setup()
{
  
  nh.initNode();
  nh.advertiseService(server1);
  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  
  
  //Serial.begin(9600);
  
  initTab();
}

void loop()
{
  nh.spinOnce();
}
