#include <Stepper.h>

//Pins actioneur linéaire
#define ACT_P1 36
#define ACT_P2 37

//Pins color sensor
#define COLOR_S0 4
#define COLOR_S1 5
#define COLOR_S2 6
#define COLOR_S3 7
#define sensorOut 8

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

String cocktail = "110110";
int cocktailInt[6];


void init_dis()
{
  while(digitalRead(finDeCourse1) == LOW)
  {
    #if motorOn
    Moteur.setSpeed(250);
    Moteur.step(NbrPas1);
    #endif
  }
  
  delay(1000);
  
  Moteur.setSpeed(250);
  Moteur.step(-NbrPas1);
  delay(2000);
  
  Moteur.setSpeed(250);
  Moteur.step(-NbrPas1);
  delay(2000);
  
  Moteur.setSpeed(250);
  Moteur.step(-NbrPas1);
  delay(2000);
  
  Moteur.setSpeed(250);
  Moteur.step(-NbrPas1);
  delay(2000);
  
  while(digitalRead(finDeCourse2) == LOW)
  {
    Moteur.setSpeed(250);
    Moteur.step(-NbrPas1);
  }
  
  positionAct = 1;
  
}

boolean goToPos(int pos)
{
  Serial.print("pos act : ");
  Serial.println(positionAct);
  Serial.print("pos voulue : ");
  Serial.println(pos);
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
  Serial.println("Avant");
  Serial.println(cocktail);
  Serial.println("Conv");
  cocktailInt[0] = tamp / 100000;
  Serial.println(cocktailInt[0] );
  cocktailInt[1] = (tamp - cocktailInt[0] * (100000)) / 10000;
  Serial.println(cocktailInt[1]);
  cocktailInt[2] = (tamp - (cocktailInt[0] * (100000) + cocktailInt[1] * (10000))) / 1000;
  Serial.println(cocktailInt[2]);
  cocktailInt[3] = (tamp - (cocktailInt[0] * (100000) + cocktailInt[1] * (10000) + cocktailInt[2] * (1000))) / 100;
  Serial.println(cocktailInt[3]);
  cocktailInt[4] = (tamp - (cocktailInt[0] * (100000) + cocktailInt[1] * (10000) + cocktailInt[2] * (1000) + cocktailInt[3] * (100))) / 10;
  Serial.println(cocktailInt[4]);
  cocktailInt[5] = (tamp - (cocktailInt[0] * (100000) + cocktailInt[1] * (10000) + cocktailInt[2] * (1000) + cocktailInt[3] * (100) + cocktailInt[4] * (10))) / 1;
  Serial.println(cocktailInt[5]);
}

void verseLiq(int dose)
{
  
  Serial.print("Dans la fonction de distribution des dose, nb dose demande : ");
  Serial.println(dose);
  for(int i=0; i<dose; i++)
  {
    Serial.print("Dose cnt : ");
    Serial.println(i);
    digitalWrite(ACT_P1,LOW);
    digitalWrite(ACT_P2,LOW);
    
    delay(1000);
    
    digitalWrite(ACT_P1,HIGH);
    digitalWrite(ACT_P2,HIGH);
    
    delay(1000);
  }
  
}



void setup()
{
  Serial.begin(9600);
  pinMode(finDeCourse1,INPUT);
  pinMode(finDeCourse2,INPUT);
  pinMode(irPresence,INPUT);
  
  pinMode(ACT_P1,OUTPUT);
  pinMode(ACT_P2,OUTPUT);
  
  pinMode(COLOR_S0,OUTPUT);
  pinMode(COLOR_S1,OUTPUT);
  pinMode(COLOR_S2,OUTPUT);
  pinMode(COLOR_S3,OUTPUT);
  pinMode(sensorOut,INPUT);
  
  digitalWrite(ACT_P1,HIGH);
  digitalWrite(ACT_P2,HIGH);
  
  digitalWrite(COLOR_S0,HIGH);
  digitalWrite(COLOR_S1,LOW);
  
  init_dis();
  Serial.println("Debut");
  convCocktail();
  
  
}



void loop()
{
  
  
  
  switch(Serial.read())
  {
    case '1':
      goToPos(1);
      break;
    case '2':
      goToPos(2);
      break;
    case '3':
      goToPos(3);
      break;
    case '4':
      goToPos(4);
      break;
    case '5':
      goToPos(5);
      break;
    case '6':
      goToPos(6);
      break;
    case 'c':
    
      if(abs(6-positionAct) > abs(0-positionAct))
      {
        Serial.println("On tourne vers le dernier liquide");
        goToPos(1);
        
        for(int i=1;i<7;i++)
        {
          Serial.print("On va a la position : ");
          Serial.println(i);
          Serial.print("Nombre de dose pour la commande : ");
          Serial.println(cocktailInt[i-1]);
          goToPos(i);
          delay(500);
          verseLiq(cocktailInt[i-1]);
        }
      }
      else
      {
        Serial.println("On tourne vers le premier liquide");
        goToPos(6);
        
        for(int i=6;i>0;i--)
        {
          Serial.print("On va a la position : ");
          Serial.println(i);
          Serial.print("Nombre de dose pour la commande : ");
          Serial.println(cocktailInt[i-1]);
          goToPos(i);
          delay(500);
          verseLiq(cocktailInt[i-1]);
        }
      }
      
      Serial.println("Fin du COCKTAIL !!");
  
  if(digitalRead(irPresence) == HIGH)
  {
    
  }
}
}

