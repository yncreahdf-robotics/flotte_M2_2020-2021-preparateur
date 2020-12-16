#define finDeCourse1 48
#define finDeCourse2 49
#define irPresence 47

#define niveau1 46
#define niveau2 45
#define niveau3 44

//Pins actioneur linéaire
#define ACT_P1 28
#define ACT_P2 29

#define driverPul 9
#define driverDir 43
#define driverEn  42

int startRotate = 0;
int finishRotate = 0;

int positionAct;

void rotateForS(int timeSec, boolean dir)
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
        delayMicroseconds(2000);
        digitalWrite(driverPul, LOW);
        delayMicroseconds(2000);
        finishRotate = millis();
      }while((finishRotate - startRotate) < timeSec);
    }
    else
    {
      do{
        digitalWrite(driverDir, HIGH);
        digitalWrite(driverPul, HIGH);
        delayMicroseconds(2000);
        digitalWrite(driverPul, LOW);
        delayMicroseconds(2000);
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
      delayMicroseconds(2000);
      digitalWrite(driverPul, LOW);
      delayMicroseconds(2000);
    }
    else
    {
      digitalWrite(driverDir, HIGH);
      digitalWrite(driverPul, HIGH);
      delayMicroseconds(2000);
      digitalWrite(driverPul, LOW);
      delayMicroseconds(2000);
    }
  }
  
  digitalWrite(driverEn,LOW);
}

void initPos()
{
  while(digitalRead(finDeCourse1) == LOW)
  {
    rotateForS(0, false);
  }
  
  delay(1000);
  rotateForS(2000, true);
  delay(2000);
  rotateForS(2000, true);
  delay(2000);
  rotateForS(2000, true);
  delay(2000);
  rotateForS(2000, true);
  delay(2000);
  
  while(digitalRead(finDeCourse2) == LOW)
  {
    rotateForS(0, true);
  }
  
  positionAct = 1;
  
}

void setup()
{
  
  Serial.begin(9600);
  pinMode(finDeCourse1,INPUT);
  pinMode(finDeCourse2,INPUT);
  pinMode(irPresence,INPUT);
  
  pinMode(niveau1,INPUT);
  pinMode(niveau2,INPUT);
  pinMode(niveau3,INPUT);
  
  pinMode(ACT_P1,OUTPUT);
  pinMode(ACT_P2,OUTPUT);
  
  pinMode(driverPul,OUTPUT);
  pinMode(driverDir,OUTPUT);
  pinMode(driverEn,OUTPUT);
  
  digitalWrite(ACT_P1,HIGH);
  digitalWrite(ACT_P2,HIGH);
  
  digitalWrite(driverEn,LOW);
  
  //initPos();
}

void loop()
{
//  Serial.print("\nCapteur fin de course 2 : ");
//  Serial.println(digitalRead(finDeCourse2));
//  Serial.print("Capteur fin de course 1 : ");
//  Serial.println(digitalRead(finDeCourse1));
//  Serial.print("Capteur IR : ");
//  Serial.println(digitalRead(irPresence));
//  Serial.print("Capteur niveau 1 : ");
//  Serial.println(digitalRead(niveau1));
//  Serial.print("Capteur niveau 2 : ");
//  Serial.println(digitalRead(niveau2));
//  Serial.print("Capteur niveau 3 : ");
//  Serial.println(digitalRead(niveau3));
//  delay(1000);

//  rotateForS(2000, false);
//  delay(2000);
//  rotateForS(2000, true);
//  delay(2000);
  
}
