#include "keypad.h"
#define CLK_Pin   2 
#define LATCH_Pin 3
#define DATA_Pin  4
#define DIN_Pin   5
#define CLO_Pin   6
#define Led_Pin   9           // PWM pin 3,5,6,9,10 and 11
#define Number_Registers 2 
unsigned int volts=0;
byte temp = 0;
/*
 * key_map:
 * FWD    ^     PRGM    247     223     254     
 * JOG    v     FUNC    239     191     127    
 *  RUN     STOP            251     253
 */

keypad keypad(CLO_Pin, LATCH_Pin, DIN_Pin);
ScanLed scanled(DATA_Pin, LATCH_Pin, CLK_Pin, Number_Registers);
int unit=0;
int ten=0;
int hund=0;
int thou=0;
void setup() {
  scanled.Clear();
  pinMode(Led_Pin,OUTPUT);
  digitalWrite(CLO_Pin,LOW);
  digitalWrite(LATCH_Pin,LOW);
}
void check()
{
  digitalWrite(LATCH_Pin,HIGH);
  byte a_temp= keypad.key_in();
  digitalWrite(LATCH_Pin,LOW);
  if(a_temp !=  temp)
  {
    temp = a_temp;
    if(temp==223)
    {
      volts++;
    }
    else if(temp==191)
    {
      if(volts!=0)
      {
        volts--; 
      }   
    }
  }
}
void convert()
{
   thou=volts/1000;
   hund=(volts%1000)/100;
   ten=((volts%1000)%100)/10;
   unit=(volts%1000)%10;
   
}
void Display()
{
  convert();
  scanled.Display(0,unit);
  if((ten!=0)|((ten==0)&((hund!=0)|(thou!=0)))){
    scanled.Display(1,ten);
  }
  else{
    ;
  }
  if((hund!=0)|((hund==0)&(thou!=0))){
    scanled.Display(2,hund);
  }
  else{
    ;
  }
  if(thou!=0){
    scanled.Display(3,thou);
    scanled.Display(3,10);
  }
  else{
    ; 
  }
  
}
void loop() {
  check();
  Display();
  analogWrite(Led_Pin,volts);
}
