#include "IRLibAll.h"
#define OUTPIN 13
 
 //Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(2);
 
//Create a decoder object 
IRdecode myDecoder;   
 
void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
  pinMode(OUTPIN, OUTPUT);

}

boolean ledOn = false;
 
void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(false);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver

    //if(myDecoder.value == 0xFFA25D) {
    ledOn = !ledOn;
    //}
  }

  if(ledOn) {
    digitalWrite(OUTPIN, HIGH);
  }
  else {
    digitalWrite(OUTPIN, LOW);    
  }
}
