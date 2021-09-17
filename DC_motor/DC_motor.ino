#include "IRLibAll.h"
 
 //Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(2);
 
//Create a decoder object 
IRdecode myDecoder;   

//L293D
// Motor A
const int motorPin1 = 6;  // Pin 14 of L293
const int motorPin2 = 5;  // Pin 10 of L293
//const int speedPinA = 11;
// Motor B
const int motorPin3 = 9; // Pin  7 of L293
const int motorPin4 = 10;  // Pin  2 of L293
//const int speedPinB = 3;

//This will run only one time.
void setup(){
    Serial.begin(9600);
    delay(2000); while (!Serial); //delay for Leonardo
    myReceiver.enableIRIn(); // Start the receiver
    Serial.println(F("Ready to receive IR signals"));
 
    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    //pinMode(speedPinA, OUTPUT);
    //pinMode(speedPinB, OUTPUT);
  
}

void cwA() {
  //This code  will turn Motor A clockwise for 2 sec.
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    //analogWrite(speedPinA, spd);
}
void ccwA() {
  //This code  will turn Motor A counterclockwise for 2 sec.
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    //analogWrite(speedPinA, spd);
}
void stopA() {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
}

void cwB() {
  //This code  will turn Motor B clockwise for 2 sec.
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    //analogWrite(speedPinB, spd);
}
void ccwB() {
  //This code  will turn Motor B counterclockwise for 2 sec.
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    //analogWrite(speedPinB, spd);
}
void stopB() {
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
}

void start_() {
    cwA();
    ccwB();  
}
void stop_() {
    stopA();
    stopB();  
}

boolean activate = false;
void loop(){
  
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(false);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver

    if(myDecoder.value == 0xFFA25D) {
      activate = !activate;
    }
    if(activate) {
      start_();
      Serial.write("on");
    }
    else {
      stop_();
      Serial.write("off");
    }
  }

  
}
