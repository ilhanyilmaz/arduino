//#include <SoftwareSerial.h>
#include <Servo.h> 

Servo mServo1;
Servo mServo2;
//SoftwareS

String message; //string that stores the incoming message

int mServoPos1 = 90;
int mServoPos2 = 90;
boolean mServoDirection = true;
int servoStep = 5;

void setup()
{
  Serial.begin(9600); //set baud rate
  mServo1.attach(9);
  mServo2.attach(10);
  mServo1.write(mServoPos1);
  mServo2.write(mServoPos2);
  Serial.print("AT+NAMEQozmoNode");
}

/*void servoActions() {
  if(mServoDirection) {
    mServoPos += servoStep;
  }
  else
    mServoPos -= servoStep;
   
  if(mServoPos > 180) {
    mServoPos = 180;
    mServoDirection = false;
  }
   else if(mServoPos<0) {
     mServoPos = 0;
     mServoDirection = true;
   }
   mServo1.write(mServoPos);
   mServo2.write(mServoPos);
}*/
char data;

void handleMessage() {
  int servoVal;
  String code = message.substring(0,5);
  //switch(code.c_str()) {
    //case "serv1":
  
  if(code.indexOf("serv1")==0) {
      mServoPos1 = atoi(message.substring(5,message.length()).c_str());
      mServo1.write(mServoPos1);
      Serial.print("Changing servo1 pos"); //show the data
      Serial.print((char)3); //show the data
  }
  else if(code.indexOf("serv2")==0) {
      mServoPos2 = atoi(message.substring(5,message.length()).c_str());
      mServo2.write(mServoPos2);
      Serial.print("Changing servo2 pos"); //show the data
      Serial.print((char)3); //show the data
  }
  else {
       Serial.print(message); //show the data
       Serial.print((char)3); //show the data
  }
}



void loop()
{
  while(Serial.available()) {
    //while there is data available on the serial monitor
    data=char(Serial.read());//store string from serial command
    switch(data) {
      case 3:
        handleMessage();
        message = "";
        break;
      default:
        message+=data;
    }   
  }
  /*if(!Serial.available())
  {
    if(message!="")
    {//if data is available
      if(message.at(message.length()-1)==3
      
      message=""; //clear the data
    }
    //else
      //Serial.println(mServoPos);
  }*/
  //servoActions();
  delay(1000); //delay
}
    
