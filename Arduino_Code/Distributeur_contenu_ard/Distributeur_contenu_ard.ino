/*
 * Tourniquet
 */

#include <ros.h>
#include <preparateur/Commande.h>
#include <preparateur/Init.h>

#include <Stepper.h>

//Pins actioneur linéaire
#define ACT_P1 36
#define ACT_P2 37


//Déclaration pins moteur
#define motorOn 1

#define IN1 28
#define IN2 29
#define IN3 30
#define IN4 31

#define finDeCourse1 22
#define finDeCourse2 49
#define irPresence 45

#define NbrPas1 100


#if motorOn
Stepper Moteur(NbrPas1, IN1, IN2, IN3, IN4);
#endif

int positionAct;

String cocktail;
int cocktailInt[6];


ros::NodeHandle  nh;


using preparateur::Commande;
using preparateur::Init;


void callbackInit(const Init::Request & req, Init::Response & res){
  nh.spinOnce();
  
  init_dis();
      
  res.success = true;
  
}

void callbackCom(const Commande::Request & req, Commande::Response & res){
  nh.spinOnce();
  
  //Réception d'une demande
  nh.loginfo("Demande commande : ");
  nh.loginfo(req.com);
  
  cocktail = req.com;
  
  convCocktail();
  
  nh.spinOnce();
  
  if(abs(6-positionAct) > abs(0-positionAct))
      {
        //Serial.println("On tourne vers le dernier liquide");
        goToPos(1);
        
        for(int i=1;i<7;i++)
        {
          nh.spinOnce();
          //Serial.print("On va a la position : ");
          //Serial.println(i);
          //Serial.print("Nombre de dose pour la commande : ");
          //Serial.println(cocktailInt[i-1]);
          goToPos(i);
          delay(500);
          verseLiq(cocktailInt[i-1]);
        }
      }
      else
      {
        //Serial.println("On tourne vers le premier liquide");
        goToPos(6);
        
        for(int i=6;i>0;i--)
        {
          nh.spinOnce();
          //Serial.print("On va a la position : ");
          //Serial.println(i);
          //Serial.print("Nombre de dose pour la commande : ");
          //Serial.println(cocktailInt[i-1]);
          goToPos(i);
          delay(500);
          verseLiq(cocktailInt[i-1]);
        }
      }
      
  res.success = true;
  
}

void init_dis()
{
  while(digitalRead(finDeCourse1) == LOW)
  {
    #if motorOn
    Moteur.setSpeed(250);
    Moteur.step(NbrPas1);
    #endif
    nh.spinOnce();
  }
  
  delay(1000);
  nh.spinOnce();
  Moteur.setSpeed(250);
  Moteur.step(-NbrPas1);
  delay(2000);
  nh.spinOnce();
  Moteur.setSpeed(250);
  Moteur.step(-NbrPas1);
  delay(2000);
  nh.spinOnce();
  Moteur.setSpeed(250);
  Moteur.step(-NbrPas1);
  delay(2000);
  nh.spinOnce();
  Moteur.setSpeed(250);
  Moteur.step(-NbrPas1);
  delay(2000);
  nh.spinOnce();
  while(digitalRead(finDeCourse2) == LOW)
  {
    Moteur.setSpeed(250);
    Moteur.step(-NbrPas1);
    nh.spinOnce();
  }
  
  positionAct = 1;
  
}

boolean goToPos(int pos)
{
  //Serial.print("pos act : ");
  //Serial.println(positionAct);
  //Serial.print("pos voulue : ");
  //Serial.println(pos);
  if(positionAct > pos)
  {
    for(int i = 0;i<(positionAct-pos);i++)
    {
      Moteur.setSpeed(250);
      Moteur.step(-NbrPas1);
      delay(2000);
      //positionAct--;  
  }
    positionAct = pos;
  }
  else if (positionAct < pos)
  {
    for(int i = 0;i<(pos-positionAct);i++)
    {
        Moteur.setSpeed(250);
        Moteur.step(NbrPas1);
        delay(2000);
        //positionAct++;
    }
    
    positionAct = pos;
  }
  else
  {
    positionAct = pos;
  }
}

void convCocktail()
{
  long tamp = cocktail.toInt();
  //Serial.println("Avant");
  //Serial.println(cocktail);
  //Serial.println("Conv");
  cocktailInt[0] = tamp / 100000;
  //Serial.println(cocktailInt[0] );
  cocktailInt[1] = (tamp - cocktailInt[0] * (100000)) / 10000;
  //Serial.println(cocktailInt[1]);
  cocktailInt[2] = (tamp - (cocktailInt[0] * (100000) + cocktailInt[1] * (10000))) / 1000;
  //Serial.println(cocktailInt[2]);
  cocktailInt[3] = (tamp - (cocktailInt[0] * (100000) + cocktailInt[1] * (10000) + cocktailInt[2] * (1000))) / 100;
  //Serial.println(cocktailInt[3]);
  cocktailInt[4] = (tamp - (cocktailInt[0] * (100000) + cocktailInt[1] * (10000) + cocktailInt[2] * (1000) + cocktailInt[3] * (100))) / 10;
  //Serial.println(cocktailInt[4]);
  cocktailInt[5] = (tamp - (cocktailInt[0] * (100000) + cocktailInt[1] * (10000) + cocktailInt[2] * (1000) + cocktailInt[3] * (100) + cocktailInt[4] * (10))) / 1;
  //Serial.println(cocktailInt[5]);
}

void verseLiq(int dose)
{
  
  //Serial.print("Dans la fonction de distribution des dose, nb dose demande : ");
  //Serial.println(dose);
  for(int i=0; i<dose; i++)
  {
    //Serial.print("Dose cnt : ");
    //Serial.println(i);
    digitalWrite(ACT_P1,LOW);
    digitalWrite(ACT_P2,LOW);
    
    //delay(2500);
    
    for(int i = 0; i<10;i++)
    {
      delay(500);
      nh.spinOnce();
    }
    
    digitalWrite(ACT_P1,HIGH);
    digitalWrite(ACT_P2,HIGH);
    
    for(int i = 0; i<10;i++)
    {
      delay(500);
      nh.spinOnce();
    }
  }
  
}

ros::ServiceServer<Commande::Request, Commande::Response> server1("/Tourniquet/commande",&callbackCom);
ros::ServiceServer<Init::Request, Init::Response> server2("/Tourniquet/init",&callbackInit);

void setup()
{
  nh.initNode();
  nh.advertiseService(server1);
  nh.advertiseService(server2);
  
  //Serial.begin(9600);
  pinMode(finDeCourse1,INPUT);
  pinMode(finDeCourse2,INPUT);
  pinMode(irPresence,INPUT);
  
  pinMode(ACT_P1,OUTPUT);
  pinMode(ACT_P2,OUTPUT);
  
  digitalWrite(ACT_P1,HIGH);
  digitalWrite(ACT_P2,HIGH);
  
  
}



void loop()
{
  nh.spinOnce();
}

