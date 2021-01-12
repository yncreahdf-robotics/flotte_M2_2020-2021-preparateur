#include <Stepper.h>

#define ACT_P1 36
#define ACT_P2 37

#define COLOR_S0 4
#define COLOR_S1 5
#define COLOR_S2 6
#define COLOR_S3 7
#define sensorOut 8

//Déclaration pins moteur
#define motorOn 0

#define IN1 28
#define IN2 29
#define IN3 30
#define IN4 31

#define NbrPas1 300

int frequency = 0;

boolean etat = false;

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

#if motorOn
Stepper Moteur(NbrPas1, IN1, IN2, IN3, IN4);
#endif

void setup()
{
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
  
  Serial.begin(9600);
}

void loop()
{
  if(Serial.read() == 'a')
  {
    digitalWrite(ACT_P1,LOW);
    digitalWrite(ACT_P2,LOW);
    
    delay(1000);
    
    digitalWrite(ACT_P1,HIGH);
    digitalWrite(ACT_P2,HIGH);
  }
  
  
  
  
  #if motorOn
  //Mouvement moteur
  Moteur.setSpeed(20);
  Moteur.step(NbrPas1);
  delay(2000);  
  #endif
  
  
  
  /*
  digitalWrite(COLOR_S2,LOW);
  digitalWrite(COLOR_S3,LOW);
  
  redFrequency = pulseIn(sensorOut, LOW);
  
  redColor = map(redFrequency, 70, 120, 255,0);
  
  //Serial.print("R = ");
  //Serial.print(redColor);
  //delay(100);
  
  digitalWrite(COLOR_S2,HIGH);
  digitalWrite(COLOR_S3,HIGH);
  
  greenFrequency = pulseIn(sensorOut, LOW);
  
  greenColor = map(greenFrequency, 100, 199, 255, 0);

  //Serial.print(" G = ");
  //Serial.print(greenColor);
  //delay(100);
 
  digitalWrite(COLOR_S2,LOW);
  digitalWrite(COLOR_S3,HIGH);
  
  blueFrequency = pulseIn(sensorOut, LOW);
  
  blueColor = map(blueFrequency, 38, 84, 255, 0);
  
  //Serial.print(" B = ");
  //Serial.print(blueColor);
  //delay(100);
  //Serial.println();
  
  if((redColor<499 && redColor>413) && (greenColor<285 && greenColor>237) && (blueColor<200 && blueColor>73))
  {
    Serial.println("ROSE");
  }
  
  if((redColor<275 && redColor>174) && (greenColor<355 && greenColor>298) && (blueColor<304 && blueColor>200))
  {
    Serial.println("BLEU");
  }
  
  if((redColor<16 && redColor>-188) && (greenColor<119 && greenColor>11) && (blueColor<-293 && blueColor>-449))
  {
    Serial.println("NOIR");
  }
  
  if((redColor<469 && redColor>357) && (greenColor<409 && greenColor>340) && (blueColor<84 && blueColor>-77))
  {
    Serial.println("JAUNE");
  }
  
  if((redColor<443 && redColor>326) && (greenColor<240 && greenColor>158) && (blueColor<-5 && blueColor>-155))
  {
    Serial.println("ROUGE");
  }
  
  if((redColor<443 && redColor>295) && (greenColor<430 && greenColor>345) && (blueColor<122 && blueColor>-155))
  {
    Serial.println("VERT");
  }
  */
}
