/*
 * Distributeur de gobelet
 */

#include <ros.h>
#include <preparateur/Commande.h>
#include <preparateur/Init.h>

#include <Stepper.h>

//Déclaration pins des capteurs
#define irStockage 48
#define irPresence 47
#define finDeCourse 49

//Déclaration pins moteur
#define motorOn 1

#define IN1 29
#define IN2 28
#define IN3 27
#define IN4 26

#define EN 46

#define NbrPas1 100

const int button_pin = 3;

bool last_reading;
long last_debounce_time=0;
long debounce_delay=50;
bool published = true;

bool occupe = false;

#define connexionOK   0
#define obstaclePB    1
#define contenantPB   2
#define contenantDis  3
#define stockPB       4

#if motorOn
Stepper Moteur(NbrPas1, IN1, IN2, IN3, IN4);


void initMot()
{
  Moteur.setSpeed(250);
  while(digitalRead(finDeCourse) == false){
     Moteur.step(NbrPas1);
   }
}

#endif

ros::NodeHandle  nh;


using preparateur::Commande;
using preparateur::Init;


void callbackCo(const Init::Request & req, Init::Response & res){
  nh.spinOnce();
  
  //Réception d'une demande
  nh.loginfo("Demande reçu : ");
  
  nh.loginfo("  Verification de la connexion");
  res.success = true;
  
}

void callbackDem(const Commande::Request & req, Commande::Response & res){
  
  nh.loginfo("  Demande d'un contenant");
  nh.loginfo("  Vérification qu'un contenant n'est pas déja présent");
  
  #if motorOn
  initMot();
  #endif
  
  delay(2000);
  
  if(digitalRead(irPresence) == false)
  {
    nh.loginfo("  Un obstacle est présent !");
    
    res.code = obstaclePB; //1
    
    
  }
  else
  {
  
    nh.loginfo("  Vérification du stock de contenant en cours ");
  
    occupe = true;
  
   
      
    if(digitalRead(irStockage) == false) //Stock présent
    {
       nh.loginfo("    OK");
       nh.loginfo("    Distribution d'un contenant en cours");
       
       #if motorOn
       //Mouvement moteur
       digitalWrite(EN, HIGH);
       Moteur.setSpeed(100);
       for(int i =0 ; i<3;i++)
       {
         Moteur.step(-NbrPas1);
       }
       delay(500);
       
       Moteur.setSpeed(100);
       
       do{
         Moteur.step(NbrPas1);
       }while(digitalRead(finDeCourse) == false);
       
       digitalWrite(EN, LOW);
       #endif
  
       //Temporisation le temps que le contenant tombe
      delay(500);
  
      if(digitalRead(irPresence) == false)
      {
        nh.loginfo("    Contenant présent");
        
        res.code = contenantDis; //3
      }
      else
      {
        nh.loginfo("    PROBLEME, le système n'a pas fonctionné");
        
        res.code = contenantPB; //2
      }
    }
    else
    {
      nh.loginfo("    PROBLEME, il n'y pas de stock");
      
      res.code = stockPB; //4
    }
   
  }
  
  nh.loginfo("FIN");
  
  res.success = true;
  
}

ros::ServiceServer<Init::Request, Init::Response> server1("/DGobelet/Init",&callbackCo);
ros::ServiceServer<Commande::Request, Commande::Response> server2("/DGobelet/Demande",&callbackDem);


void setup()
{
  nh.initNode();
  nh.advertiseService(server1);
  nh.advertiseService(server2);
  
  //Configuration du moteur
  #if motorOn
  Moteur.setSpeed(40);
  #endif

  pinMode(irStockage,INPUT);
  pinMode(irPresence,INPUT);
  pinMode(finDeCourse,INPUT);
  
  pinMode(EN, OUTPUT);
  
  digitalWrite(EN, LOW);
}

void loop()
{
  nh.spinOnce();
}
