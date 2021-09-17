#include <IRLibAll.h>
 
IRsend mySender;

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int ledPin = 13;
const int IRpin = 3;

long duration, cm;
long normalDistance;
long threshold = 5;

boolean currentlySensing = false;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   
   pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);
   
   pinMode(ledPin, OUTPUT);
   //pinMode(IRpin, OUTPUT);

  //when the arduino starts up, ping the distance one time so you know what "normal" is
   ping();
   normalDistance = microsecondsToCentimeters(duration);
}

void loop() {
  ping();
     
  cm = microsecondsToCentimeters(duration);
  if(cm < normalDistance - threshold) {// if distance is significantly closer than normal
    if(!currentlySensing) {
      mySender.send(NEC, 0xFFA25D); //send a signal using the NEC encoding scheme with the message FFA25D
    }
    currentlySensing = true;
    digitalWrite(ledPin, HIGH);
  }
  else {
    currentlySensing = false;
    digitalWrite(ledPin, LOW);
  }
  delay(100);
}

//long microsecondsToInches(long microseconds) {
//   return microseconds / 74 / 2;
//}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void ping() {
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
}
