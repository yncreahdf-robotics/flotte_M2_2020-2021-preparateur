#include <ros.h>
#include <preparateur/Stockage.h>
#include <preparateur/Commande.h>
#include <preparateur/Init.h>
#include <std_msgs/Int64.h>

#include <Stepper.h>

#define finDeCourse1 48
#define finDeCourse2 49


#define IN1 42
#define IN2 43
#define IN3 44
#define IN4 45

#define EN 23

#define NbrPas1 20

bool etat = false;

Stepper Moteur(NbrPas1, IN1, IN2, IN3, IN4);

const byte interruptPin1 = 2;
const byte interruptPin2 = 3;

std_msgs::Int64 positionG;


String stockage;
ros::NodeHandle  nh;

using preparateur::Stockage;
using preparateur::Commande;
using preparateur::Init;


void goToPostion(String pos)
{
  digitalWrite(EN, HIGH);
  //Serial.print("Flavie mouette");
  if(pos == "1")
  {
    positionG.data = 1;
    //Serial.println("pelican");
    do{
     Moteur.setSpeed(50);
     Moteur.step(-NbrPas1);
     //Serial.println("Je tourne -->");
    }while(digitalRead(finDeCourse2) != HIGH);

  } 

  if(pos == "2")
  {
    positionG.data = 2;
    do{
     Moteur.setSpeed(50);
     Moteur.step(NbrPas1);
     //Serial.println("Je tourne <--");
    }while(digitalRead(finDeCourse1) != HIGH);

  }
  //digitalWrite(EN, LOW);
}



void callbackSto(const Init::Request & req, Init::Response & res){

  //Réception d'une demande
  nh.loginfo("Demande reçu : ");
  
  nh.loginfo("  Renvoie de la position du stock");
  res.code = positionG.data;  
  res.success = true;
  
}

void callbackPos(const Commande::Request & req, Commande::Response & res){

  //Réception d'une demande
  nh.loginfo("Demande reçu : ");
  String pre = req.com;
  int pos = pre.toInt();
  if(pos == 1)
  {
    nh.loginfo("Je tourne");
    goToPostion("1");
  }
  
  if(pos == 2)
  {
    goToPostion("2");
  }
  res.success = true;
  
}

ros::ServiceServer<Init::Request, Init::Response> server1("/Stockage/Demande",&callbackSto);
ros::ServiceServer<Commande::Request, Commande::Response> server2("/Stockage/Position",&callbackPos);

void setup() {
  
  nh.initNode();
  nh.advertiseService(server1);
  nh.advertiseService(server2);
  
  pinMode(EN, OUTPUT);
  
  goToPostion("1");
  positionG.data = 1;

  //Serial.begin(9600);
}

void loop() {


  nh.spinOnce();
}
