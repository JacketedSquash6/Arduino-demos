#include "LedControl.h"
#include "binary.h"

const int VRx = A0;
const int VRy = A1;
const int SW = 2;
/*
 DIN connects to pin 10
 CLK connects to pin 8
 CS connects to pin 9 
*/
LedControl lc=LedControl(10,8,9,1);

// delay time between faces
unsigned long delaytime=1000;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

boolean picture[8][8] {0};
int joystickThreshold = 300;
int posX = 0;
int posY = 0;

void setup() {
  Serial.begin(9600); 
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,1);
  // Clear the display
  lc.clearDisplay(0);    
}

//    -Y
//-X      +X
//    +Y

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  if(SW_state == 0) {
    memset(picture, 0, 64);
  }
  if(mapX < -joystickThreshold) {
    posX = (posX + 7) % 8;
  }
  if(mapX > joystickThreshold) {
    posX = (posX + 1) % 8;
  }
  if(mapY < -joystickThreshold) {
    posY = (posY + 7) % 8;
  }
  if(mapY > joystickThreshold) {
    posY = (posY + 1) % 8;
  }
  picture[posY][posX] = 1;

  draw(picture);
  
  delay(200);
}

void draw(byte picture[]) {
  for(int i = 0; i < 8; i++) {
    lc.setRow(0, i, picture[i]);
  }
}
void draw(boolean picture[8][8]) {
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      lc.setLed(0, i, j, picture[i][j]);
    }
  }
}

//// happy face
//byte hf[8]= {B00111100,B01000010,B10100101,B10000001,B10100101,B10011001,B01000010,B00111100};
//// neutral face
//byte nf[8]={B00111100, B01000010,B10100101,B10000001,B10111101,B10000001,B01000010,B00111100};
//// sad face
//byte sf[8]= {B00111100,B01000010,B10100101,B10000001,B10011001,B10100101,B01000010,B00111100};
//
//
//void drawFaces(){
//  draw(sf);
//  delay(delaytime);
//  
//  draw(nf);
//  delay(delaytime);
//  
//  draw(hf);
//  delay(delaytime);
//}
