/*
 * Distributeur de gobelet
 */

#include <ros.h>
#include <test_serial_arduino/Connexion.h>
#include <test_serial_arduino/DemandeContenant.h>

#include <Stepper.h>

//Déclaration pins des capteurs
#define irStockage 3
#define irPresence 4
#define finDeCourse 2

//Déclaration pins moteur
#define motorOn 0

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

#define NbrPas1 300

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
  Moteur.setSpeed(10);
  while(digitalRead(finDeCourse) == false){
     Moteur.step(100);
   }
}

#endif

ros::NodeHandle  nh;


using test_serial_arduino::Connexion;
using test_serial_arduino::DemandeContenant;


void callbackCo(const Connexion::Request & req, Connexion::Response & res){
  nh.spinOnce();
  
  //Réception d'une demande
  nh.loginfo("Demande reçu : ");
  
  nh.loginfo("  Verification de la connexion");
  res.success = true;
  
}

void callbackDem(const DemandeContenant::Request & req, DemandeContenant::Response & res){
  
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
       Moteur.setSpeed(20);
       Moteur.step(-NbrPas1);
       delay(2000);
       
       Moteur.setSpeed(10);
       
       do{
         Moteur.step(100);
       }while(digitalRead(finDeCourse) == false);
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

ros::ServiceServer<Connexion::Request, Connexion::Response> server1("co_distrib_contenant",&callbackCo);
ros::ServiceServer<DemandeContenant::Request, DemandeContenant::Response> server2("dem_distrib_contenant",&callbackDem);


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
}

void loop()
{
  nh.spinOnce();
}
