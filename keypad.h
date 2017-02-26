#ifndef keypad_h
#define keypad_h

class keypad
{
  public:
    keypad(int CLO_Pin,int LATCH_Pin,int DIN_Pin);
    byte key_in();

  private:
    int _CLO_Pin;
    int _LATCH_Pin;
    int _DIN_Pin;
    byte _key;
};


class ScanLed
{
 public:
  ScanLed(int DATA_Pin,int CLK_Pin,int LATCH_Pin,int Num_of_HC595);
   int check();
   void Display(int led,int val);
   void Clear();
  
  private:
   int _CheckPin;
   int _sensor;
   int _volts;
   int _DATA_Pin;
   int _LATCH_Pin;
   int _CLK_Pin;
   int _pinState;
    
   int _Num_of_HC595;     
   byte _shiftRegs[14];
   
};
#endif
