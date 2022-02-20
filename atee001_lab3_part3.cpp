const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;
const int b7 = 9;

#define a0 digitalRead(A0)
#define a1 digitalRead(A1)

int led_Pins[] = {2,3,4,5,6,7,8,9};

void writeToB(unsigned char temp)
{

Serial.println(temp);

if ((temp>>7) & 0x01){digitalWrite(b7,HIGH);}
else digitalWrite(b7,LOW);
if ((temp>>6) & 0x01){digitalWrite(b6,HIGH);}
else digitalWrite(b6,LOW);
if ((temp>>5) & 0x01){digitalWrite(b5,HIGH);}
else digitalWrite(b5,LOW);
if ((temp>>4) & 0x01){digitalWrite(b4,HIGH);}
else digitalWrite(b4,LOW);
if ((temp>>3) & 0x01){digitalWrite(b3,HIGH);}
else digitalWrite(b3,LOW);
if ((temp>>2) & 0x01){digitalWrite(b2,HIGH);}
else digitalWrite(b2,LOW);
if ((temp>>1) & 0x01){digitalWrite(b1,HIGH);}
else digitalWrite(b1,LOW);
if (temp & 0x01){digitalWrite(b0,HIGH);}
else digitalWrite(b0,LOW);
}

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
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


//0000
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

enum states{start, inc, dec, reset, wait} state = start;
unsigned char value;

void Tick(){
  switch(state){
  case start:
      Serial.println("start");
      if(a0 && !a1) state = inc;
      else if(!a0 && a1) state = dec;
        else if(a0 && a1) state = reset;
        else state = start;
        value = 7;
        writeToB(value);
      break;
    case inc:
      Serial.println("inc");
      state = wait;
      writeToB(++value);
      delay(200);
      break;
     case dec:
      Serial.println("dec");
      state = wait;
      writeToB(--value);
      delay(200);
      break;
     case reset:
      Serial.println("reset");
      state = wait;
      value = 0;
      writeToB(value);
      break;
     case wait:
      Serial.println("wait");
      if((a0 && !a1) && value < 10) state = inc;
      else if((!a0 && a1) && value > 0) state = dec;
        else if(a0 && a1) state = reset;
        else state = wait;
        break;
  }

}
void loop(){

  
    Tick();

}
