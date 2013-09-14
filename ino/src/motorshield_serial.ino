#include <AFMotor.h>
#include <Servo.h> 

int posS1 = 0;         // variable to store the servo position
int posS2 = 0;         // variable to store the servo position
int posS1i = 0;        // servo 1 initial position
int posS2i = 0;        // servo 2 initial position
int incomingByte = 0;  // for incoming serial data
int currentPosS1;      //current position servo 1
int currentPosS2;      //current position servo 2
int speedDC1 = 0;      //DC motor 1 speed
int speedDC2 = 0;      //DC motor 2 speed

AF_DCMotor motor1(2,MOTOR12_64KHZ);
AF_DCMotor motor2(4,MOTOR34_64KHZ);
Servo servo1;  // create servo object to control a servo. A maximum of eight servo objects can be created 
Servo servo2;  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Arduino code starting");

  servo1.attach(9);  // attaches the servo on pin 9 to the servo object 
  servo2.attach(10);  // attaches the servo on pin 9 to the servo object 
  servo1.write(posS1i); //set the servo position to 0 degrees
  servo2.write(posS2i); //set the servo position to 0 degrees

  motor1.setSpeed(50);
  motor1.run(RELEASE);
  motor2.setSpeed(50);
  motor2.run(RELEASE);

  /* ascii codes for the keys to de used:
   a = 97
   s= 115
   d = 100
   w = 119
   x = 120
   h = 104
   H = 72
   j = 106
   J = 74
   k = 107
   l = 108
   */

}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);

  switch(incomingByte){
    case 97: 
      if(posS1 > 180){
        posS1=170;
      }
      posS1 += 10; 
      servo1.write(posS1);
      currentPosS1 = servo1.read();
      Serial.print("S1 Current position: ");
      Serial.println(currentPosS1);
      break;
    case 100:
      if(posS1 < 0){
        posS1=10;
      }
      posS1 -= 10; 
      servo1.write(posS1);
      currentPosS1 = servo1.read();
      Serial.print("S1 Current position: ");
      Serial.println(currentPosS1);
      break;
    case 119:
      if(posS2 > 180){
        posS2=170;
      }
      posS2 += 10; 
      servo2.write(posS2);
      currentPosS2 = servo2.read();
      Serial.print("S2 Current position: ");
      Serial.println(currentPosS2);      
      break;
    case 115:
      if(posS2 < 0){
        posS2=10;
      }
      posS2 -= 10; 
      servo2.write(posS2);
      currentPosS1 = servo2.read();
      Serial.print("S2 Current position: ");
      Serial.println(currentPosS2);
      break;
    case 120:
      Serial.println("Reset servo to default position");
      servo1.write(posS1i);
      servo2.write(posS2i);
      posS1 = 0;
      posS2 = 0;
      break;
    case 104:
      motor1.setSpeed(127);
      motor1.run(FORWARD);
      break;
    case 72:
      motor1.run(RELEASE); 
      break;
    case 106:
      motor1.setSpeed(127);
      motor1.run(BACKWARD);
      break;
    case 74:
      motor1.run(RELEASE); 
      break;
    case 107:
      motor2.setSpeed(127);
      motor2.run(FORWARD);
      delay(2500);
      motor2.run(RELEASE); 
      delay(250);
      break;
    case 108:
      motor2.setSpeed(127);
      motor2.run(BACKWARD);
      delay(2500);
      motor2.run(RELEASE); 
      delay(250);
      break;
    default:
      incomingByte = 0;
    }
  Serial.print("S1 Current position requested: ");
  Serial.println(posS1);
  Serial.print("S2 Current position requested: ");
  Serial.println(posS2);
  incomingByte = 0;
  }  
}

