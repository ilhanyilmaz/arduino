#define L1 A3
#define L2 A5
#define L3 A4
boolean L1Val = 0;
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);



void setup() {
  ADCSRA &= ~PS_128;
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
  Serial.begin(115200);
  analogReference(INTERNAL);
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  Mouse.begin();
}
const int MINVAL = 25;
const int ROTATING = 1;
const int DIRECTION_C = 2; //clockwise
const int POS_L1 = 4;
const int POS_L2 = 8;
const int POS_L3 = 16;

int prevStatus = 0;
void loop() {
  int l1 = analogRead(L1);
  int l2 = analogRead(L2);
  int l3 = analogRead(L3);  
  int myPosition = 0;
  int maxV = 0;
  if( l1 + l2 + l3 > MINVAL) {
    
    
    maxV= max(l1,l2);
    maxV= max(maxV, l3);
    if(maxV == l1) {
      myPosition = POS_L1;
      if(l1 - (l2+l3) < 5)
        return;
    }
    else if(maxV == l2) {
      myPosition = POS_L2;
      if(l2 - (l1+l3) < 5)
        return;
    }
    else {
      myPosition = POS_L3;
      if(l3 - (l1+l2) < 5)
        return;
    }    
    Serial.print(l1);
    Serial.print("\t");
    Serial.print(l2);
    Serial.print("\t");
    Serial.print(l3);
    Serial.print("\t:");
    Serial.print(myPosition);
    Serial.print(prevStatus&(POS_L1|POS_L2|POS_L3));
    Serial.print("\t:");
    /*if(l1 == 0)
      myPosition = POS_L1;
    else if(l2 == 0)
      myPosition = POS_L2;
    else
      myPosition = POS_L3;*/
    
    switch(prevStatus&(POS_L1|POS_L2|POS_L3)) {
       case POS_L1:
         if(myPosition == POS_L1)
           myPosition = prevStatus;
         else if(myPosition  == POS_L2)
           myPosition = myPosition | ROTATING | DIRECTION_C;  // rotating in clockwise
         else if(myPosition  == POS_L3)
           myPosition = myPosition | ROTATING; // rotating in counterclockwise
         else
           Serial.println("wow");
         break;
       case POS_L2:
         if(myPosition == POS_L2)
           myPosition = prevStatus;
         else if(myPosition == POS_L3)
           myPosition = myPosition | ROTATING | DIRECTION_C;  // rotating in clockwise
         else if(myPosition == POS_L1)
           myPosition = myPosition | ROTATING; // rotating in counterclockwise
         else
           Serial.println("wow");
         break;
       case POS_L3:
         if(myPosition == POS_L3)
           myPosition = prevStatus;
         else if(myPosition == POS_L1)
           myPosition = myPosition | ROTATING | DIRECTION_C;  // rotating in clockwise
         else if(myPosition == POS_L2)
           myPosition = myPosition | ROTATING; // rotating in counterclockwise
         else
           Serial.println("wow");
         break;
       //default: case 0:    
    }
    Serial.println((myPosition&DIRECTION_C)?  Mouse.move(0, 0, 1);:  Mouse.move(0, 0, -1););
    prevStatus = myPosition;
  }
  // move the mouse:

  delay(responseDelay);
}
