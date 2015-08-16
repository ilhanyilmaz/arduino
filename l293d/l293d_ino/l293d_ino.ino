
int pot1Pin = A1;    // select the input pin for the potentiometer
int pot2Pin = A2;    // select the input pin for the potentiometer
int pot1Target=600;
int pot2Target=600;
int motorA1Pin = 5;
int motorA2Pin = 6;
int motorB1Pin = 10;
int motorB2Pin = 11;
int interval = 5;
String message; //string that stores the incoming message
char data;

///////////////////////////////////////////////////////////////
//
// Servo pos formula = 5x + 100
//
//////////////////////////////////////////////////////////////

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
//  Serial.println("test");
  Serial.print("AT+NAMEQozmoNode");
  pinMode(motorA1Pin, OUTPUT);
  pinMode(motorA2Pin, OUTPUT);
  pinMode(motorB1Pin, OUTPUT);
  pinMode(motorB2Pin, OUTPUT);
}

void servoActions() {
  int sensorValue = analogRead(pot1Pin);
  int diff = pot1Target - sensorValue;
  if(abs(diff) > interval) {
    if(sensorValue > pot1Target) {
        digitalWrite(motorA1Pin,LOW);
        digitalWrite(motorA2Pin,HIGH);
    }
    else {
        digitalWrite(motorA1Pin,HIGH);
        digitalWrite(motorA2Pin,LOW);
    }
  }
  else {
        digitalWrite(motorA1Pin,LOW);
        digitalWrite(motorA2Pin,LOW);
  }
//  Serial.println(sensorValue, DEC);
  sensorValue = analogRead(pot2Pin);
  diff = pot2Target - sensorValue;
  if(abs(diff) > interval) {
    if(sensorValue > pot2Target) {
        digitalWrite(motorB1Pin,LOW);
        digitalWrite(motorB2Pin,HIGH);
    }
    else {
        digitalWrite(motorB1Pin,HIGH);
        digitalWrite(motorB2Pin,LOW);
    }
  }
  else {
        digitalWrite(motorB1Pin,LOW);
        digitalWrite(motorB2Pin,LOW);
  }
}

int translateAngle(int angle) {
  return angle * 5 + 100;
}

void handleMessage() {
  int angle;
  String code = message.substring(0,5);
  //switch(code.c_str()) {
    //case "serv1":
  
  if(code.indexOf("serv1")==0) {
      angle = atoi(message.substring(5,message.length()).c_str());
      pot1Target = translateAngle(angle);
      Serial.print("Changing servo1 pos"); //show the data
      Serial.print((char)3); //show the data
  }
  else if(code.indexOf("serv2")==0) {
      angle = atoi(message.substring(5,message.length()).c_str());
      pot2Target = translateAngle(angle);
      Serial.print("Changing servo2 pos"); //show the data
      Serial.print((char)3); //show the data
  }
  else {
      message = "nocode: " + message;
       Serial.print(message); //show the data
       Serial.print((char)3); //show the data
  }
}

void loop() {
  // read the value from the sensor:
   
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
  servoActions();
  delay(50);
}
