
#include <Wire.h>
#include <Servo.h>

#define SLAVE_ADDRESS 0x04

Servo myservo;  // create servo object to control a servo 
Servo myservo2;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position 
int pos2 = 90;    // variable to store the servo position 
int targetAngle = 90;
int targetAngle2 = 90;

void setup() 
{ 
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);

  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  
  Serial.println("Ready!");

  myservo.attach(2);  // attaches the servo on pin 9 to the servo object 
  myservo2.attach(4);  // attaches the servo on pin 9 to the servo object 
  //pinMode(inputPin1, INPUT);
  //pinMode(inputPin2, INPUT);
} 

void receiveData(int byteCount){
  while(Wire.available()) {
    int readValue = Wire.read();
    
    if(readValue < 128)
      targetAngle = readValue;
    else
      targetAngle2 = readValue - 128;

      
    Serial.print("data received:");
    Serial.println(readValue);
  }
}

void sendData() {
  Wire.write(targetAngle);
}
void servoControl()
{
  if(pos < targetAngle )
      pos += 1;
  else if(pos > targetAngle)
      pos -= 1;
  myservo.write(pos);              // tell servo to go to position in variable 'pos' 
  if(pos2 < targetAngle2 )
      pos2 += 1;
  else if(pos2 > targetAngle2)
      pos2 -= 1;
  myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
  delay(15);
}

void loop() 
{ 
  servoControl();
}
