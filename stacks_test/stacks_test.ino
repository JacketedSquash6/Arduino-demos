struct StackNode {
  int val;
  StackNode* next;
};

typedef void (*action)(StackNode** head, int x);
struct Operation {
  int val;
  action a;
};

const int numOperations = 30;
int operationsCursor = 0;
Operation* operations = (Operation*)malloc(sizeof(Operation) * numOperations);

const int inputLength = 20;
int inputCursor = 0;
char* input = (char*)malloc(sizeof(char) * inputLength);

void setup() {
  Serial.begin(9600);

  Serial.println("-------------");
  StackNode** head = (StackNode**)malloc(sizeof(StackNode*));
  *head = NULL;

  for(int i = 0; i < numOperations; i++) {
    operations[i].val = 0;
    operations[i].a = stackDoNothing;
  }
  for(int i = 0; i < inputLength; i++) {
    input[i] = ' ';
  }
  
//  input[0]  = '(';
//  input[1]  = '3';
//  input[2]  = '*';
//  input[3]  = '5';
//  input[4]  = '*';
//  input[5]  = '2';
//  input[6]  = '+';
//  input[7]  = '2';
//  input[8]  = '*';
//  input[9]  = '(';
//  input[10] = '1';
//  input[11] = '2';
//  input[12] = '-';
//  input[13] = '2';
//  input[14] = ')';
//  input[15] = ')';
//  input[16] = '/';
//  input[17] = '1';
//  input[18] = '0';
//  input[0]  = '(';
//  input[1]  = '5';
//  input[2]  = '-';
//  input[3]  = '2';
//  input[4]  = ')';
//  input[5]  = '*';
//  input[6]  = '4';
//  input[7]  = '-';
//  input[8]  = '1';
  input = "364/0                      ";
  Serial.println(input);

  parseAddition();

  for(int i = 0; i < numOperations; i++) {
    Serial.print(operations[i].val);
    Serial.print("  ");
    operations[i].a(head, operations[i].val);
    stackPeek(head, 0);
  }

  Serial.print("Result: ");
  Serial.println(pop(head));

}

void loop() {
  // put your main code here, to run repeatedly:
  
}

char peekChar() {
  if(inputCursor == inputLength) {
    //return ' ';
  }
  return input[inputCursor];
}
char parseChar() {
  if(inputCursor == inputLength) {
    //return ' ';
  }
  char output = input[inputCursor];
  inputCursor += 1;
  return output;
}

void parseAddition() {
  parseMultiplication();
  while(peekChar() == '+' || peekChar() == '-') {
    char c = parseChar();
    if(c == '+') {
      parseMultiplication();
      addOperation(0, stackAdd);
    }
    else if (c == '-') {
      parseMultiplication();
      addOperation(0, stackSubtract);
    }
  }
}
void parseMultiplication() {
  parseNumber();
  while(peekChar() == '*' || peekChar() == '/') {
    char c = parseChar();
    if(c == '*') {
      parseNumber();
      addOperation(0, stackMultiply);
    }
    else if (c == '/') {
      parseNumber();
      addOperation(0, stackDivide);
    }
  }
}
void parseNumber() {
  boolean conc = false;
  boolean paren = false;
  
  while(peekChar() != ' ' && peekChar() != '+' && peekChar() != '-' && peekChar() != '*' && peekChar() != '/' && (paren || peekChar() != ')')) {
    char c = parseChar();
    switch(c) {
      case '0':
        addOperation(0, (conc ? stackConcatenate : push)); conc = true; break;
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
        parseAddition(); paren = true; break;
      case ')':
        paren = false; break;
    }
  }
}

void addOperation(int val, action a) {
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
void stackSubtract(StackNode** head, int x) { //the x has to be there so it's the same type of function as push
  int a = pop(head);
  int b = pop(head);
  push(head, b - a);
}
void stackMultiply(StackNode** head, int x) {
  int a = pop(head);
  int b = pop(head);
  push(head, b * a);
}
void stackDivide(StackNode** head, int x) {
  int a = pop(head);
  int b = pop(head);
  push(head, b / a);
}
void stackConcatenate(StackNode** head, int val) { //unary concatenation
  int a = pop(head);
  push(head, a*10 + val);
}

void push(StackNode** head, int val) {
  StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
  newNode->val = val;
  newNode->next = *head;
  *head = newNode;
}

int pop(StackNode **head) {
  if(*head == NULL) {
    return 0;
  }
  int output = (*head)->val;
  *head = (*head)->next;
  return output;
}
