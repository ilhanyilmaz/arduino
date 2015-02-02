
// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A4;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A5;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int sensorValue2 = 0;        // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}
int value =0;
int value2 =0;
int cycle = 0;
void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  sensorValue2 = analogRead(analogInPin2);            
  // map it to the range of the analog out:



  if(sensorValue>0)
    value++;

  if(sensorValue2>0)
    value2++;
    
  if(cycle==64) {
      // print the results to the serial monitor:
    Serial.print("sensor = " );                       
    Serial.print(value);
    Serial.print(" - " );                       
    Serial.println(value2);
    cycle=0;
    value=0;
    value2=0;
  }
  cycle++;
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}
