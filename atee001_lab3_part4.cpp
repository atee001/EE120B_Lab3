const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;
const int b7 = 9;

#define a0 digitalRead(A0) ? 1:0
#define a1 digitalRead(A1) ? 1:0
#define a2 digitalRead(A2) ? 1:0
#define a4 digitalRead(A4) ? 1:0

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A3, INPUT);
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  pinMode(b6, OUTPUT);
  pinMode(b7, OUTPUT);
  Serial.begin(9600);
}

void resetB()
{
digitalWrite(b7,LOW);
digitalWrite(b6,LOW);
digitalWrite(b5,LOW);
digitalWrite(b4,LOW);
digitalWrite(b3,LOW);
digitalWrite(b2,LOW);
digitalWrite(b1,LOW);
digitalWrite(b0,LOW);
}

enum states {lock, pound_press, pound_rel, y_press, unlock} state = lock;

void Tick(){

switch(state){
  case lock:
    if(a1 && !a0 && !a2) state = pound_press;
    else state = lock;
    resetB();
    break;
  case pound_press:
    if(a1 && !a0 && !a2) state = pound_press;
    else if(!a0 && !a1 && !a2) state = pound_rel;
    else state = lock;
    break;
  case pound_rel:
    if(!a1 && !a0 && !a1) state = y_press;
    else if(a0 || a2) state = lock;
    else state = pound_rel;
    break;
   case y_press:
    if(a2 && !a1 && !a0) state = unlock;
    else if(a1 || a0) state = lock;
    else state = y_press;
    break;
   case unlock:
    state = (a4) ? lock : unlock;
    digitalWrite(b2, HIGH);    
  }
  
}
  
  



void loop() {
  Tick();
}
