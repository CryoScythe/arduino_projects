# Maze Solving Bot
The bot is designed and programmed to make its way through a maze

The bot must perform the following functions:
1) Walk straight until reaching a dead end
2) Check left and right distances.
3) Move in direction of maximum distances.

Working Idea:
1) Run both wheel motors in forward direction.
2) Stop if distance less than 15mm
3) Turn sensor bearing servo right and left and record the ping
4) Rotate dc motors to turn the bot to left or right.
5) Continue forward motion

Constraints:
1) The bot, when faced with a dead end, the path with maximum distance must be the correct pathway.
2) The bot, shouldn't find a T-point with branching from main path.

Circuit Diagram:
![Alt text](/CryoScythe/arduino_projects/Circuit_Representation.png?raw=true "Bot - circuit diagram")

```C
#include<Servo.h>
Servo myservo;\\Object myservo created
int usspin = 7;\\Ultrasonic sensor(PING) pin
int servoPin = 3;\\Servo pin
int dc1e = 6;\\DC motor 1 enabler
int dc2e = 10;\\DC motor 2 enabler
int dc1c1 = 11;\\DC motor 1 control 1
int dc1c2 = 12;\\DC motor 1 control 2
int dc2c1 = 8;\\DC motor 1 control 1
int dc2c2 = 9;\\DC motor 1 control 2
int len,dist,left,right;

void setup()\\Initiation
{
  Serial.begin(9600);\\Declaration of begin
  myservo.attach(servoPin);\\Attaching servo to pin
  pinMode(dc1e, OUTPUT);
  pinMode(dc2e, OUTPUT);
  pinMode(dc1c1, OUTPUT);
  pinMode(dc1c2, OUTPUT);
  pinMode(dc2c1, OUTPUT);
  pinMode(dc2c2, OUTPUT);
  myservo.write(90);\\Initial postition of servo at 90 degrees
  delay(1000);
}

void turnl()\\Fuction to turn the bot left
{
  digitalWrite(dc1e, HIGH);\\Enabling dc 1
  digitalWrite(dc2e, HIGH);\\Enabling dc 2
  
  digitalWrite(dc1c1, LOW);
  digitalWrite(dc1c2, HIGH);\\Turning dc 1 in clockwise direction
  
  digitalWrite(dc2c1, HIGH);
  digitalWrite(dc2c2, LOW);\\Turning dc 2 in anti-clockwise direction
  delay(1000);
}
 void turnr()
{
  digitalWrite(dc1e, HIGH);\\Enabling dc 1
  digitalWrite(dc2e, HIGH);\\Enabling dc 2
  
  digitalWrite(dc1c1, HIGH);
  digitalWrite(dc1c2, LOW);\\Turning dc 1 in anti-clockwise direction
    
  digitalWrite(dc2c1, LOW);
  digitalWrite(dc2c2, HIGH);\\Turning dc 2 in clockwise direction
  delay(1000);
}
  
int microsecTocm(int microsec)\\To convert ping time to distance
{
  return microsec/29/2;
}
  
int ussread()\\Throwing and reading echo in ultrasonic sensor 
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

void checkdir()\\Checking distances left and right
{
  myservo.write(0);\\Turn servo left
  delay(1000);
  left=ussread();
  myservo.write(179);\\Turn servo right
  delay(1000);
  right=ussread();
  myservo.write(89);
  if(left>=right)
    turnl();
  else
    turnr();
}

void loop()\\Continues infinitely
{
 if(ussread()<=15)
 {
   digitalWrite(dc1e, LOW);\\Stops dc 1
   digitalWrite(dc2e, LOW);\\Stops dc 2
   checkdir();
  }
  else
  {
   digitalWrite(dc1e, HIGH);\\Enabling dc 1
   digitalWrite(dc2e, HIGH);\\Enabling dc 2
   digitalWrite(dc1c1, HIGH);
   digitalWrite(dc1c2, LOW);\\Turns dc 1 clockwise
   digitalWrite(dc2c1, HIGH);
   digitalWrite(dc2c2, LOW);\\Turns dc 2 clockwise
   delay(1000);
  }
}
```
