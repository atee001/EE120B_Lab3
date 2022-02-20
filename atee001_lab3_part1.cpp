const int b0 = 2;
const int b1 = 3;
unsigned char count = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  Serial.begin(9600);
}
enum butt_States {start, butt_press_1, butt_release, butt_press_2} butt_State = start;

void Tick(){
  
  switch(butt_State){ //transitions
    case start:
      butt_State = (digitalRead(A0) == HIGH) ? butt_press_1 : start;
      Serial.println("S1");
      
      break;        
    
    case butt_press_1:
      butt_State = (digitalRead(A0) == HIGH) ? butt_press_1 : butt_release;
      Serial.println("S2");
      break; 

     case butt_release:
      butt_State = (digitalRead(A0) == HIGH) ? butt_press_2 : butt_release;
      Serial.println("S3");
      break;

     case butt_press_2:
      butt_State = butt_press_2;
      Serial.println("S4");
      break;  

     default:
       butt_State = start;
 
       Serial.println("Error!");
       break;

       
  }

  switch(butt_State){ //actions
    case start:
      digitalWrite(b0, HIGH);
      digitalWrite(b1, HIGH);      
      break;        
    
    case butt_press_1:
      digitalWrite(b0, LOW);
      digitalWrite(b1, HIGH);
      break;

     case butt_release:
      digitalWrite(b0, LOW);
      digitalWrite(b1, HIGH);
      break;

     case butt_press_2:
      digitalWrite(b0, HIGH);
      digitalWrite(b1, LOW);
      break;      

      default:
       Serial.println("Error!");
       break;
  }
  delay(200);
}


void resetB()
{
digitalWrite(b1,LOW);
digitalWrite(b0,LOW);
}

void loop() {
  resetB();
  
  Tick();
  
}
