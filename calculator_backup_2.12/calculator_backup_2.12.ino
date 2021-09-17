#include <LiquidCrystal.h>

const int potentiometerPin = 2;

const int a = 24;  //For displaying segment "a"      AAA
const int b = 22;  //For displaying segment "b"     F   B
const int c = 25;  //For displaying segment "c"     F   B
const int d = 27;  //For displaying segment "d"      GGG
const int e = 29;  //For displaying segment "e"     E   C
const int f = 26;  //For displaying segment "f"     E   C
const int g = 28;  //For displaying segment "g"      DDD .
const int dot = 23;  //For displaying dot on 7seg display

const int numButtons = 9;


int btn[numButtons];
boolean buttonReady[numButtons];

typedef void (*voidFunction)();
voidFunction buttonHandler[numButtons];



int val = 0;
int digit = 0;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


void setup() {
  Serial.begin(9600);
  
  pinMode(potentiometerPin, INPUT);
  
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
  pinMode(dot, OUTPUT);  //7seg dot

  btn[0] = 31;
  btn[1] = 45;
  btn[2] = 44;
  btn[3] = 43;
  btn[4] = 42;
  btn[5] = 41;
  btn[6] = 40;
  btn[7] = 39;
  btn[8] = 38;
  for (int i = 0; i < numButtons; i++) {
    pinMode(btn[i], INPUT);
    digitalWrite(btn[i], HIGH);
  }

  buttonHandler[0] = buttonHandler0;
  buttonHandler[1] = buttonHandler1;
  buttonHandler[2] = buttonHandler2;
  buttonHandler[3] = buttonHandler3;
  buttonHandler[4] = buttonHandler4;
  buttonHandler[5] = buttonHandler5;
  buttonHandler[6] = buttonHandler6;
  buttonHandler[7] = buttonHandler7;
  buttonHandler[8] = buttonHandler8;

  lcd.begin(16,2);
}

void loop() {
  update7seg();
  handleButtons();
  
  delay(100);
}


//    ####################
//    # helper functions #
//    ####################

void update7seg() {
  val = analogRead(potentiometerPin); 
  digit = map(val, 0, 1024, 0, 10);
  //Serial.println(val);
  turnOff();
  displayDigit(digit);
}

void handleButtons() {
  for(int i = 0; i < numButtons; i++) {
    if(digitalRead(btn[i]) == LOW) { //if it is low, the current went to ground, and therefore the button is pushed
      if(buttonReady[i]) {
        buttonHandler[i]();
      }
      buttonReady[i] = false;    
    } 
    else {
      buttonReady[i] = true;
    }
  }
}

void buttonHandler0(){
  lcd.print(digit);
}
void buttonHandler1(){
  lcd.print("+");
}
void buttonHandler2(){
  lcd.print("-");
}
void buttonHandler3(){
  lcd.print("*");
}
void buttonHandler4(){
  lcd.print("/");
}
void buttonHandler5(){
  lcd.print("(");
}
void buttonHandler6(){
  lcd.print(")");
}
void buttonHandler7(){
  lcd.print("d");
}
void buttonHandler8(){
  lcd.print("e");
}
void buttonHandlerDefault(){
  Serial.println("This button not implemented");
}

void displayDigit(int digit)
{
 //Conditions for displaying segment a
 if(digit!=1 && digit != 4)
 digitalWrite(a,HIGH);
 
 //Conditions for displaying segment b
 if(digit != 5 && digit != 6)
 digitalWrite(b,HIGH);
 
 //Conditions for displaying segment c
 if(digit !=2)
 digitalWrite(c,HIGH);
 
 //Conditions for displaying segment d
 if(digit != 1 && digit !=4 && digit !=7)
 digitalWrite(d,HIGH);
 
 //Conditions for displaying segment e 
 if(digit == 2 || digit ==6 || digit == 8 || digit==0)
 digitalWrite(e,HIGH);
 
 //Conditions for displaying segment f
 if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
 digitalWrite(f,HIGH);
 if (digit!=0 && digit!=1 && digit !=7)
 digitalWrite(g,HIGH);
 
}
void turnOff()
{
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
}
