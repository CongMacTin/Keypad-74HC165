#include "Arduino.h"
#include "keypad.h"

keypad::keypad(int CLO_Pin,int LATCH_Pin,int DIN_Pin)
{
    _CLO_Pin  = CLO_Pin;
    _LATCH_Pin= LATCH_Pin;
    _DIN_Pin  = DIN_Pin;  
  
    pinMode( _CLO_Pin,OUTPUT);
    pinMode( _LATCH_Pin,OUTPUT);
    pinMode( _DIN_Pin,INPUT); 
    
     byte key_in();
  
}
byte keypad::key_in()
{
  _key  = 0; 
  for(int i =0; i<8; i++)
    {
      digitalWrite(_CLO_Pin,HIGH);
      _key  = _key | (digitalRead(_DIN_Pin)<<i);
      digitalWrite(_CLO_Pin,LOW);
    }
  return _key;
}  
/*

 */
 ScanLed::ScanLed(int DATA_Pin, int CLK_Pin, int LATCH_Pin, int Num_of_HC595){  
 
  _DATA_Pin = DATA_Pin;
  _CLK_Pin = CLK_Pin;
  _LATCH_Pin = LATCH_Pin;
  _Num_of_HC595 = Num_of_HC595;

  pinMode(_CheckPin,INPUT); 
  pinMode(_DATA_Pin, OUTPUT);
  pinMode(_CLK_Pin, OUTPUT);
  pinMode(_LATCH_Pin, OUTPUT);
  void check(int volts); 
  void Clear(); //reset all register pins
  void Display(int led,int val);
}

void ScanLed::Display(int led,int val)
{
 boolean pinState;
 int sel[]={0x01,0x02,0x04,0x08,0x10};
 int seg[]={0xee,0x88,0xd6,0xdc,0xb8,0x7c,0x7e,0xc8,0xfe,0xfc,0x01};
 
 int selLed=sel[led];
 int dataOut=seg[val]; 

 int shift[]={dataOut,selLed};
  
 digitalWrite(_CLK_Pin,LOW);
   for(int i=_Num_of_HC595-1;i>=0;i--)
     {
       for(int j=8-1;j>=0;j--)
        { 
          digitalWrite(_LATCH_Pin,HIGH);

          pinState=shift[i]&(1<<j);

          digitalWrite(_DATA_Pin,pinState);   
          digitalWrite(_LATCH_Pin,LOW);   
        }
      }
    digitalWrite(_CLK_Pin,HIGH); 
 }

void ScanLed::Clear()
{
 boolean pinState;
 
 for(int k=0;k<5;k++)
  {
   int sel[]={0x01,0x02,0x04,0x08,0x10};
   int shift[]={0x00,sel[k]};
   
   digitalWrite(_CLK_Pin,LOW);
     for(int i=_Num_of_HC595-1;i>=0;i--)
      {
       for(int j=8-1;j>=0;j--)
        { 
          digitalWrite(_LATCH_Pin,HIGH);

          pinState=shift[i]&(1<<j);

          digitalWrite(_DATA_Pin,pinState);   
          digitalWrite(_LATCH_Pin,LOW);   
        }
      }
    digitalWrite(_CLK_Pin,HIGH);
  }
}

int ScanLed::check()
{
    _sensor= analogRead(_CheckPin);
    _volts=map(_sensor,0,1023,0,10000);
    return _volts;
 }
