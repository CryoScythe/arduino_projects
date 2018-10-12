#include<Servo.h>
Servo myservo;
int usspin = 7;
int servoPin = 3;
int dc1e = 6;
int dc2e = 10;
int dc1c2 = 12;
int dc1c1 = 11;
int dc2c1 = 8;
int dc2c2 = 9;

int len,dist,left,right;

void setup()
{
  Serial.begin(9600);
  myservo.attach(servoPin);
  pinMode(dc1e, OUTPUT);
  pinMode(dc2e, OUTPUT);
  pinMode(dc1c1, OUTPUT);
  pinMode(dc1c2, OUTPUT);
  pinMode(dc2c1, OUTPUT);
  pinMode(dc2c2, OUTPUT);
  myservo.write(90);
  delay(1000);
}

void turnl()
{
  digitalWrite(dc1e, HIGH);
  digitalWrite(dc2e, HIGH);
  digitalWrite(dc1c1, LOW);
  digitalWrite(dc1c2, HIGH);
  digitalWrite(dc2c1, HIGH);
  digitalWrite(dc2c2, LOW);
  delay(1000);
}
void turnr()
{
  digitalWrite(dc1e, HIGH);
  digitalWrite(dc2e, HIGH);
  digitalWrite(dc1c1, HIGH);
  digitalWrite(dc1c2, LOW);
  digitalWrite(dc2c1, LOW);
  digitalWrite(dc2c2, HIGH);
  delay(1000);
}
  
int microsecTocm(int microsec)
{
  return microsec/29/2;
}
  
int ussread()
{
  pinMode(usspin, OUTPUT);
  digitalWrite(usspin, LOW);
  delayMicroseconds(2);
  digitalWrite(usspin, HIGH);
  delayMicroseconds(5);
  digitalWrite(usspin, LOW);
  pinMode(usspin,INPUT);
  len = pulseIn(usspin, HIGH);
  dist=microsecTocm(len);
  return (dist);
}

void checkdir()
{
  myservo.write(0);
  delay(1000);
  left=ussread();
  Serial.print("\nleft=");
  Serial.print(left);
  myservo.write(179);
  delay(1000);
  right=ussread();
  Serial.print("\nright=");
  Serial.print(right);
  myservo.write(89);
  if(left>=right)
  {turnl();Serial.print("Turning Left");}
  else
  {turnr(); Serial.print("Turning Right");}
}

void loop()
{
  if(ussread()<=15)
  {
    digitalWrite(dc1e, LOW);
    digitalWrite(dc2e, LOW);    
    checkdir();
  }
  else
  {
    digitalWrite(dc1e, HIGH);
    digitalWrite(dc2e, HIGH);
    digitalWrite(dc1c1, HIGH);
    digitalWrite(dc1c2, LOW);
    digitalWrite(dc2c1, HIGH);
    digitalWrite(dc2c2, LOW);
    delay(1000);
  }
}
