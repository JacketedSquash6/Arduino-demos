#include <LiquidCrystal.h>

// <Math code>

//When we compile the math, it will be turned from a string into reverse-Polish notation. 
//It will then be a linked-list of Operations describing what actions to do to a number stack.
//For example, to compute (2+3)*4, we will have the following operations:
//1) Add 2 to the stack
//2) Add 3 to the stack
//3) Take the 2 most recent values from the stack, add them, and put the sum back to the stack
//4) Add 4 to the stack
//5) Take the 2 most recent values from the stack, multiply them, and put the product back to the stack

struct StackNode { //StackNodes are what keeps track of the numbers in the stack and keeps them in order
  int val;
  StackNode* next;
};

typedef void (*action)(StackNode** head, int x); //an action is a type of function that acts on the stack with a given integer variable

struct Operation { //an operation is a struct that holds a value and a specific action. When we execute the code, 
                   //we will go through our list of operations and execute their actions with their values
  int val;
  action a;
};

const int numOperations = 30; //the maximum number of operations our code can handle
int operationsCursor = 0; //where in our operations array we are currently writing
Operation* operations = (Operation*)malloc(sizeof(Operation) * numOperations); //dynamically allocated operations array

const int inputLength = 20; //how long of a math string we can handle
int inputCursor = 0; //where in the input we are currently writing
char* input = (char*)malloc(sizeof(char) * inputLength); //a String representing the input

// </Math code>

// <Hardware code>
const int potentiometerPin = 2; //pin of digit potentiometer
int val = 0; //the value read by the potentiometer
int digit = 0; //the digit corresponding to that value

const int a = 24;  //For displaying segment "a"      AAA
const int b = 22;  //For displaying segment "b"     F   B
const int c = 25;  //For displaying segment "c"     F   B
const int d = 27;  //For displaying segment "d"      GGG
const int e = 29;  //For displaying segment "e"     E   C
const int f = 26;  //For displaying segment "f"     E   C
const int g = 28;  //For displaying segment "g"      DDD .
const int dot = 23;  //For displaying dot on 7seg display

              // 0   1   2   3   4   5   6
int btn[9]; //the 9 pins representing the 9 buttons
boolean buttonReady[9]; //an array of booleans representing whether the button is currently pressed (False) or if it is ready to be pressed again (True)

typedef void (*voidFunction)(); 
voidFunction buttonHandler[9]; //an array of 9 functions telling us what to do for each of the 9 buttons


LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
// <Hardware code/>

void setup() {
  Serial.begin(9600);

  setupPins();

  setupButtons();

  lcd.begin(16,2);

  for(int i = 0; i < inputLength; i++) { //initialize input string to spaces
    input[i] = ' ';
  }
  resetMath();
}

void loop() {
  // update 7seg display based on potentiometer
  val = analogRead(potentiometerPin); 
  digit = map(val, 0, 1024, 0, 10);
  //Serial.println(val);
  turnOff(); //clear the 7seg display
  displayDigit(digit); //write the current digit to the 7seg display

  handleButtons();
  
  delay(100);
}


//    ####################
//    # helper functions #
//    ####################

void setupPins() {
  pinMode(potentiometerPin, INPUT);
  
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
  pinMode(dot, OUTPUT);  //7seg dot  
}
void setupButtons() {
  btn[0] = 31;
  btn[1] = 45;
  btn[2] = 44;
  btn[3] = 43;
  btn[4] = 42;
  btn[5] = 41;
  btn[6] = 40;
  btn[7] = 39;
  btn[8] = 38;
  for (int i = 0; i < 9; i++) {
    pinMode(btn[i], INPUT);
    digitalWrite(btn[i], HIGH); //write high to each pin so they will go low when pressed and connected to ground
  }

  buttonHandler[0] = buttonHandler0; //this allows us to access the buttonHandler functions from an array
  buttonHandler[1] = buttonHandler1;
  buttonHandler[2] = buttonHandler2;
  buttonHandler[3] = buttonHandler3;
  buttonHandler[4] = buttonHandler4;
  buttonHandler[5] = buttonHandler5;
  buttonHandler[6] = buttonHandler6;
  buttonHandler[7] = buttonHandler7;
  buttonHandler[8] = buttonHandler8;  
}
void resetMath() {  
  for(int i = 0; i < numOperations; i++) {
    operations[i].val = 0;
    operations[i].a = stackDoNothing;
  }
}

void handleButtons() {
  for(int i = 0; i < 9; i++) {
    if(digitalRead(btn[i]) == LOW) { //if it is low, the current went to ground, and therefore the button is pushed
      if(buttonReady[i]) { //if the button isn't ready, we already handled it so we should do nothing
        lcd.clear();
        buttonHandler[i]();
        lcd.write(input);
      }
      buttonReady[i] = false;    
    } 
    else {
      buttonReady[i] = true; //if the button isn't pushed it should get ready to be pushed again
    }
  }
}

void buttonHandler0(){ //button0 is the digit button
  input[inputCursor] = ('0' + digit); // '0'+digit adds the digit to the ascii value of 0. for example, if digit is 5, we will write '0' + 5 = 48 + 5 = 53 to imput
  inputCursor += 1; //move cursor over one
}
void buttonHandler1(){ //button1 is the plus button
  input[inputCursor] = ('+');
  inputCursor += 1;
}
void buttonHandler2(){ //button2 is the minus button
  input[inputCursor] = ('-');
  inputCursor += 1;
}
void buttonHandler3(){ //button3 is the multiply button
  input[inputCursor] = ('*');
  inputCursor += 1;
}
void buttonHandler4(){ //button4 is the divide button
  input[inputCursor] = ('/');
  inputCursor += 1;
}
void buttonHandler5(){ //button5 is the left-paren button
  input[inputCursor] = ('(');
  inputCursor += 1;
}
void buttonHandler6(){ //button6 is the right-paren button
  input[inputCursor] = (')');
  inputCursor += 1;
}
void buttonHandler7(){ //button7 is the delete button
  if(inputCursor > 0) { //if we have anythign written, delete it
    inputCursor -= 1;
  }
  input[inputCursor] = (' ');
}
void buttonHandler8(){ //button8 is the enter button
  
  StackNode** head = (StackNode**)malloc(sizeof(StackNode*)); //construct a stack
  *head = NULL; //start with no numbers in it

  int temp = inputCursor;
  inputCursor = 0; //have to reset the cursor to 0 for it to parse the math properly
  
  Serial.println(input);
  
  parseAddition(); //parse the input
  //that function will fill the operations stack

  for(int i = 0; i < numOperations; i++) {
    Serial.print(operations[i].val); //for debugging
    Serial.print("  ");
    operations[i].a(head, operations[i].val); //for every operation, do it's action, with the stack being head and the value being the value in the operation
    stackPeek(head, 0);
  }

  lcd.setCursor(0, 1);  //go to the second line
  lcd.print(pop(head)); //print whatever was in the stack at the end
  lcd.setCursor(0, 0);  //go back to the first line

  resetMath(); //clear the stack and operations array
  inputCursor = temp; //put the cursor back where it was so the user can keep typing
}

void displayDigit(int digit) //this code is stolen. It handles writing digits to the 7seg display
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
void turnOff() //turns off every segment in the 7seg display
{
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
}

//    ##################
//    # math functions #
//    ##################

char peekChar() { //check the next character in the input string
  if(inputCursor == inputLength) {
    //return ' ';
  }
  return input[inputCursor];
}
char parseChar() { //return the next character in the input string and advance the cursor
  if(inputCursor == inputLength) {
    //return ' ';
  }
  char output = input[inputCursor];
  inputCursor += 1;
  return output;
}

void parseAddition() {
  parseMultiplication(); //since PEMDAS puts multiplication before addition, we should first resolve any multiplicative clauses we see
  while(peekChar() == '+' || peekChar() == '-') { //if, after resolving multiplication, we see a plus or minus, we need to add or subtract whatever comes after
    char c = parseChar(); //c stores either the plus or minus we find
    if(c == '+') {
      parseMultiplication(); //first we see what was after the plus or minus
      addOperation(0, stackAdd); //then we add the operation to add the two uppermost values together. This happens in this order because we are using reverse-polish notation
    }
    else if (c == '-') {
      parseMultiplication(); //ditto for subtraction
      addOperation(0, stackSubtract);
    }
  }
}
void parseMultiplication() {
  parseNumber(); //if we see numbers or parenthesis, we need to resolve those
  while(peekChar() == '*' || peekChar() == '/') { //if after the numbers/parenthesis we see a multiplication or division sign, we have to multiply or divide whatever follows
    char c = parseChar();
    if(c == '*') {
      parseNumber(); //first we find whatever follows
      addOperation(0, stackMultiply); //then we add the operation telling us to multiply the values together
    }
    else if (c == '/') {
      parseNumber(); //ditto for division
      addOperation(0, stackDivide);
    }
  }
}
void parseNumber() {
  boolean conc = false; //if we are seeing the first number after an operation, we should not be concatenating. 
                        //if we are looking at several consecutive numbers, they should concatenate on each-other
  boolean paren = false;  //are we currently inside a set of parenthesis?
  
  while(peekChar() != ' ' && peekChar() != '+' && peekChar() != '-' && peekChar() != '*' && peekChar() != '/' && (paren || peekChar() != ')')) { //we expect to see either a number, a left-paren, or a right paren
                                                                                                                                                 //however, if we see a right paren, we should currently be inside parenthesis
    char c = parseChar();
    switch(c) {
      case '0':
        addOperation(0, (conc ? stackConcatenate : push)); conc = true; break; //if we see a number and we know we should concatenate, add the operation stackConcatenate. if not, add the operation push. either way, the next number should concatenate
      case '1':
        addOperation(1, (conc ? stackConcatenate : push)); conc = true; break;
      case '2':
        addOperation(2, (conc ? stackConcatenate : push)); conc = true; break;
      case '3':
        addOperation(3, (conc ? stackConcatenate : push)); conc = true; break;
      case '4':
        addOperation(4, (conc ? stackConcatenate : push)); conc = true; break;
      case '5':
        addOperation(5, (conc ? stackConcatenate : push)); conc = true; break;
      case '6':
        addOperation(6, (conc ? stackConcatenate : push)); conc = true; break;
      case '7':
        addOperation(7, (conc ? stackConcatenate : push)); conc = true; break;
      case '8':
        addOperation(8, (conc ? stackConcatenate : push)); conc = true; break;
      case '9':
        addOperation(9, (conc ? stackConcatenate : push)); conc = true; break;
      case '(':
        parseAddition(); paren = true; break; //if we see an open-paren, treat whatever is inside as it's own clause to be parsed. also keep in mind that we are now inside parenthesis
      case ')':
        paren = false; break; //if we were previously inside parenthesis, we no longer are.
    }
  }
}

void addOperation(int val, action a) { //add an operation to the operations array
  if(operationsCursor == numOperations) {
    //return;
  }
  operations[operationsCursor].val = val;
  operations[operationsCursor].a = a;
  operationsCursor += 1;
}


void stackDoNothing(StackNode** head, int x) { //does nothing
}
void stackPeek(StackNode** head, int x) { //peek at top number
  Serial.print("Peek: ");
  Serial.println((*head)->val);
}
void stackAdd(StackNode** head, int x) { //adds the top two items in the stack
  int a = pop(head);
  int b = pop(head);
  push(head, b + a);
}
void stackSubtract(StackNode** head, int x) { //subtracts the top two items in the stack
  int a = pop(head);
  int b = pop(head);
  push(head, b - a);
}
void stackMultiply(StackNode** head, int x) { //multiplies the top two items in the stack
  int a = pop(head);
  int b = pop(head);
  push(head, b * a);
}
void stackDivide(StackNode** head, int x) { //floor-divides the top two items in the stack
  int a = pop(head);
  int b = pop(head);
  push(head, b / a);
}
//although the above functions don't use the x they are given,
//the x has to be there so it's the same type of function that 'action' can store

void stackConcatenate(StackNode** head, int val) { //unary concatenation
  int a = pop(head);
  push(head, a*10 + val); //take whatever number was on top, and make it so it has another digit at the end
}

void push(StackNode** head, int val) { //put a value on top of the stack
  StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
  newNode->val = val;
  newNode->next = *head;
  *head = newNode;
}

int pop(StackNode **head) { //take the top value off the stack
  if(*head == NULL) {
    return 0;
  }
  int output = (*head)->val;
  *head = (*head)->next;
  return output;
}
