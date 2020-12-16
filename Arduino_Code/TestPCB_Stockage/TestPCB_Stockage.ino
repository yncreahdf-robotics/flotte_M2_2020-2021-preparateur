#include <Stepper.h>

#define finDeCourse1 48
#define finDeCourse2 49

#define IN1 42
#define IN2 43
#define IN3 44
#define IN4 45

#define NbrPas1 20

Stepper Moteur(NbrPas1, IN1, IN2, IN3, IN4);

void setup()
{
  
  Serial.begin(9600);
  pinMode(finDeCourse1,INPUT);
  pinMode(finDeCourse2,INPUT);
}

void loop()
{
//  Serial.print("\nCapteur fin de course 2 : ");
//  Serial.println(digitalRead(finDeCourse2));
//  Serial.print("Capteur fin de course 1 : ");
//  Serial.println(digitalRead(finDeCourse1));
//  delay(1000);

//     Moteur.setSpeed(50);
//     Moteur.step(-NbrPas1);
}
