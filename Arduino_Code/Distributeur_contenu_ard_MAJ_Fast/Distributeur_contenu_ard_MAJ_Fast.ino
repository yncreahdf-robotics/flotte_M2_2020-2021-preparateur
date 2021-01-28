/*
 * Tourniquet
 */

#include <ros.h>
#include <preparateur/Commande.h>
#include <preparateur/Init.h>

#include <Stepper.h>

#define systemOK       0
#define systemNotOK    1
#define emptyBottle    2
#define niryoNotHere   3

//Pins actioneur linéaire
#define ACT_P1 28
#define ACT_P2 29

//Capteurs de niveau
#define niveau1 46
#define niveau2 45
#define niveau3 44

//Déclaration pins moteur
#define motorOn 1

//#define IN1 28
//#define IN2 29
//#define IN3 30
//#define IN4 31
#define driverPul 9
#define driverDir 43
#define driverEn  42

#define finDeCourse1 48
#define finDeCourse2 49
#define irPresence 47

//#define NbrPas1 100


#if motorOn
//Stepper Moteur(NbrPas1, IN1, IN2, IN3, IN4);
#endif

int startRotate = 0;
int finishRotate = 0;

int positionAct;

String cocktail;
int cocktailInt[6];

boolean initS = false;


ros::NodeHandle  nh;


using preparateur::Commande;
using preparateur::Init;


void callbackState(const Init::Request & req, Init::Response & res){
    nh.spinOnce();
  
  //Réception d'une demande
  nh.loginfo("Demande reçu : ");
  
  nh.loginfo("  Verification de la connexion");
  res.success = true;
}

void callbackInit(const Init::Request & req, Init::Response & res){
  nh.loginfo("Demande d'initialisation du systeme");
  nh.spinOnce();
  nh.loginfo("  Initialisation de la position");
  initPos();
  nh.loginfo("  Verification des liquides");    
  res.code = liquideState();
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
  
  if(!digitalRead(irPresence))
  {
   
    if(abs(6-positionAct) > abs(0-positionAct))
        {    
         
          for(int i=1;i<7;i++)
          {
            nh.spinOnce();
            
            if(cocktailInt[i-1] != 0)
            {
              goToPos(i);
              delay(500);
              verseLiq(cocktailInt[i-1]);
            }
          }
        }
        else
        {
          for(int i=6;i>0;i--)
          {
            nh.spinOnce();
            
            if(cocktailInt[i-1] != 0)
            {
              goToPos(i);
              delay(500);
              verseLiq(cocktailInt[i-1]);
            }
          }
        }
        initS = true;
        res.code =  systemOK;
        res.success = true;
  }
  else
  {
    nh.logerror("  Gobelet non present !!"); 
    res.code =  niryoNotHere;
    res.success = false;
  }
  
}


void rotateForS(int timeSec, boolean dir, int vit)
{
  startRotate = millis();
  finishRotate = 0;
  
  digitalWrite(driverEn,HIGH);
  
  if(timeSec != 0)
  {
    if(dir)
    {
      do{
        digitalWrite(driverDir, LOW);
        digitalWrite(driverPul, HIGH);
        delayMicroseconds(vit);
        digitalWrite(driverPul, LOW);
        delayMicroseconds(vit);
        finishRotate = millis();
      }while((finishRotate - startRotate) < timeSec);
    }
    else
    {
      do{
        digitalWrite(driverDir, HIGH);
        digitalWrite(driverPul, HIGH);
        delayMicroseconds(vit);
        digitalWrite(driverPul, LOW);
        delayMicroseconds(vit);
        finishRotate = millis();
      }while((finishRotate - startRotate) < timeSec);
    }
  }
  else
  {
    if(dir)
    {
      digitalWrite(driverDir, LOW);
      digitalWrite(driverPul, HIGH);
      delayMicroseconds(vit);
      digitalWrite(driverPul, LOW);
      delayMicroseconds(vit);
    }
    else
    {
      digitalWrite(driverDir, HIGH);
      digitalWrite(driverPul, HIGH);
      delayMicroseconds(vit);
      digitalWrite(driverPul, LOW);
      delayMicroseconds(vit);
    }
  }
  
  digitalWrite(driverEn,LOW);
}

int liquideState()
{
  if(digitalRead(niveau1) == LOW || digitalRead(niveau2) == LOW || digitalRead(niveau3) == LOW)
  {
    return emptyBottle;
  }
  else
  {
    return systemOK;
  }
}

void initPos()
{
  nh.loginfo("Go to pos 6");
  digitalWrite(driverEn,HIGH);
  while(digitalRead(finDeCourse1) == LOW)
  {
    //rotateForS(0, false);
    digitalWrite(driverDir, LOW);
    digitalWrite(driverPul, HIGH);
    delayMicroseconds(6000);
    digitalWrite(driverPul, LOW);
    delayMicroseconds(6000);
    nh.spinOnce();
  }
  digitalWrite(driverEn,HIGH);
  
  delay(1000);
  nh.loginfo("Pos 5");
  nh.spinOnce();
  rotateForS(2000, false, 4000);
  
  delay(2000);
  
  rotateForS(1080, false, 1000);
  nh.loginfo("Pos 4");
  nh.spinOnce();
  rotateForS(2250, false, 4000);
  
  delay(2000);
  
  rotateForS(1080, false, 1000);
  nh.loginfo("Pos 3");
  nh.spinOnce();
  rotateForS(2250, false, 4000);
  
  delay(2000);
  
  rotateForS(1080, false, 1000);
  nh.loginfo("Pos 2");
  nh.spinOnce();
  rotateForS(2250, false, 4000);
  
  delay(2000);
  nh.spinOnce();
  digitalWrite(driverEn,HIGH);

  while(digitalRead(finDeCourse2) == LOW)
  {
    //rotateForS(0, true);
    digitalWrite(driverDir, HIGH);
    digitalWrite(driverPul, HIGH);
    delayMicroseconds(6000);
    digitalWrite(driverPul, LOW);
    delayMicroseconds(6000);
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
  //nh.loginfo("Go to pos" );
  String test = "Go to pos " +  String(pos);
  nh.loginfo(test.c_str());
  
  if(pos != positionAct)
  {
    if(pos == 1 || pos == 6)
    {
      switch(pos){
        case 1:
          digitalWrite(driverEn,HIGH);
          nh.loginfo("Go to pos 1");
          while(digitalRead(finDeCourse2) == LOW)
          {
            //rotateForS(0, true);
            digitalWrite(driverDir, HIGH);
            digitalWrite(driverPul, HIGH);
            delayMicroseconds(6000);
            digitalWrite(driverPul, LOW);
            delayMicroseconds(6000);
            nh.spinOnce();
          }
          break;
        case 6:
          digitalWrite(driverEn,HIGH);
          nh.loginfo("Go to pos 6");
          while(digitalRead(finDeCourse1) == LOW)
          {
            //rotateForS(0, false);
            digitalWrite(driverDir, LOW);
            digitalWrite(driverPul, HIGH);
            delayMicroseconds(6000);
            digitalWrite(driverPul, LOW);
            delayMicroseconds(6000);
            nh.spinOnce();
          }
          
          digitalWrite(driverEn,HIGH);
          break;
      }
      positionAct = pos;
    }
    else
    {
      if(positionAct > pos)
      {
        //nh.loginfo("Rotation de type 1");
        for(int i = 0;i<(positionAct-pos);i++)
        {
          //rotateForS(2000, false, 4000);
          
          nh.spinOnce();
          rotateForS(2250, false, 4000);
          rotateForS(1080, false, 1000);
           
        }
        positionAct = pos;
      }
      else if (positionAct < pos)
      {
        //nh.loginfo("Rotation de type 2");
        for(int i = 0;i<(pos-positionAct);i++)
        {
          //rotateForS(2000, true, 4000);
          
          nh.spinOnce();
          rotateForS(2250, true, 4000);
          rotateForS(1080, true, 1000);
        }
        
        positionAct = pos;
      }
      else
      {
        positionAct = pos;
      }
    }
  }
  else
  {
    nh.loginfo("On est deja a la bonne position");
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
  String doseStr = "Demande de " + String(dose) + "Du liquide " + String(positionAct);
  
  nh.loginfo(doseStr.c_str());
  
  
  
  for(int i=0; i<dose; i++)
  {
    //Serial.print("Dose cnt : ");
    //Serial.println(i);
    digitalWrite(ACT_P1,LOW);
    digitalWrite(ACT_P2,LOW);
    
    //delay(2500);
    
    for(int i = 0; i<14;i++)
    {
      delay(500);
      nh.spinOnce();
    }
    
    digitalWrite(ACT_P1,HIGH);
    digitalWrite(ACT_P2,HIGH);
    
    for(int i = 0; i<14;i++)
    {
      delay(500);
      nh.spinOnce();
    }
  }
  
}

ros::ServiceServer<Commande::Request, Commande::Response> server1("/Tourniquet/commande",&callbackCom);
ros::ServiceServer<Init::Request, Init::Response> server2("/Tourniquet/init",&callbackInit);
ros::ServiceServer<Init::Request, Init::Response> server3("/Tourniquet/State",&callbackState);

void setup()
{
  nh.initNode();
  nh.advertiseService(server1);
  nh.advertiseService(server2);
  nh.advertiseService(server3);
  
  //Serial.begin(9600);
  pinMode(finDeCourse1,INPUT);
  pinMode(finDeCourse2,INPUT);
  pinMode(irPresence,INPUT);
  
  pinMode(ACT_P1,OUTPUT);
  pinMode(ACT_P2,OUTPUT);
  
  digitalWrite(ACT_P1,HIGH);
  digitalWrite(ACT_P2,HIGH);
  
  pinMode(niveau1,INPUT);
  pinMode(niveau2,INPUT);
  pinMode(niveau3,INPUT);
  
  pinMode(driverPul,OUTPUT);
  pinMode(driverDir,OUTPUT);
  pinMode(driverEn,OUTPUT);
  
  //Moteur désactivé
  digitalWrite(driverEn,LOW);
}



void loop()
{
  nh.spinOnce();
  
  if(initS == true)
  {
    if(positionAct<4)
    {
      for(int i= positionAct;i>0;i--)
      {
        goToPos(i);
      }
      
    }
    else
    {
      for(int i = positionAct;i<7;i++)
      {
        goToPos(i);
      }
    }
    initS = false;
  }
}

