
#include "RC5.h"

int IR_PIN = 2;
unsigned long t0;
RC5 rc5(IR_PIN);
unsigned long softwareTimer=0;
unsigned long timeoutTimer=0;

unsigned char pwmValueBig_desired=0;
unsigned char pwmValueBig_actual=0;
unsigned char bigButtonLock=0;
unsigned char pwmValueLittle_desired=0;
unsigned char pwmValueLittle_actual=0;
unsigned char littleButtonLock=0;


void setup(void) {

  pinMode(4, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  blinky(10);
}
 
void loop(void) {

  unsigned char toggle;
  unsigned char address;
  unsigned char command;
  if (rc5.read(&toggle, &address, &command))
  {
    //big Power on/off (green PowerButton) 
    if(command==61&&bigButtonLock==0)   
    {
      //lock powerbutton for at least 10*15ms
      bigButtonLock=10;
      if(pwmValueBig_actual==pwmValueBig_desired)
      {
        if(pwmValueBig_actual==0)
        pwmValueBig_desired=255;
        if(pwmValueBig_actual!=0)
        pwmValueBig_desired=0;
      }else
      {
        pwmValueBig_desired=pwmValueBig_actual;
      }
    }
    //big - (channel down)
    if(command==33)
    {
      if(pwmValueBig_desired-9>0)
      {
        pwmValueBig_desired-=9;
      }else
      {
        pwmValueBig_desired=0;
      }
    }
    //big + (channel up)
    if(command==32)
    {
      if(pwmValueBig_desired+10<255)
      {
        pwmValueBig_desired+=10;
      }else
      {
        pwmValueBig_desired=255;
      }
    }

    //little Power on/off (house symbol Button) 
    if(command==59&&littleButtonLock==0)   
    {
      //lock house button for at least 10*15ms
      littleButtonLock=10;
      if(pwmValueLittle_actual==pwmValueLittle_desired)
      {
        if(pwmValueLittle_actual==0)
        pwmValueLittle_desired=255;
        if(pwmValueLittle_actual!=0)
        pwmValueLittle_desired=0;
      }else
      {
        pwmValueLittle_desired=pwmValueLittle_actual;
      }
    }
    //little - (Volume -)
    if(command==17)
    {
      if(pwmValueLittle_desired-9>0)
      {
        pwmValueLittle_desired-=9;
      }else
      {
        pwmValueLittle_desired=0;
      }
    }
    //little + (Volume +)
    if(command==16)
    {
      if(pwmValueLittle_desired+10<255)
      {
        pwmValueLittle_desired+=10;
      }else
      {
        pwmValueLittle_desired=255;
      }
    }
    //switch off
    if(command==0) timeoutTimer=0;
    //10min
    if(command==1) timeoutTimer=40000;
    //20min
    if(command==2) timeoutTimer=80000;
    if(command==3) timeoutTimer=120000;
    if(command==4) timeoutTimer=160000;
    if(command==5) timeoutTimer=200000;
    if(command==6) timeoutTimer=240000;
    if(command==7) timeoutTimer=280000;
    if(command==8) timeoutTimer=320000;
    if(command==9) timeoutTimer=360000;
  }
  
  /*this whole block is called every 15.000ms*******************************/
  if((micros()-softwareTimer)>15000)
  {
    softwareTimer=micros();
    if(bigButtonLock) bigButtonLock--;
    if(littleButtonLock) littleButtonLock--;
    //convience timer to timeout all LEDs after xxx minutes
    if(timeoutTimer) timeoutTimer--;
    if(timeoutTimer==1)
    {
      timeoutTimer=0;  
      pwmValueBig_desired=0;
      pwmValueLittle_desired=0;
    }
    
    if(pwmValueBig_actual<pwmValueBig_desired)
    {
      pwmValueBig_actual++;
    }
    if(pwmValueBig_actual>pwmValueBig_desired)
    {
      pwmValueBig_actual--;
    }
    
    if(pwmValueLittle_actual<pwmValueLittle_desired)
    {
      pwmValueLittle_actual++;
    }
    if(pwmValueLittle_actual>pwmValueLittle_desired)
    {
      pwmValueLittle_actual--;
    }
  }


  /*PWM OUT*******************************/
  if(pwmValueBig_actual!=0)
  {
    pinMode(0, OUTPUT);
    //PIN 0 = PWM output big 
    analogWrite(0,pwmValueBig_actual);
  }else
  {
    digitalWrite(0, LOW);
  }
  if(pwmValueLittle_actual!=0)
  {
    pinMode(4, OUTPUT);
    //PIN 0 = PWM output big 
    analogWrite(4,pwmValueLittle_actual);
  }else
  {
    digitalWrite(4, LOW);
  }
  
  //PIN 1 = PWM output little to LED
  analogWrite(1,pwmValueLittle_actual);


}

void blinky(int times)
{
  times++;
  for(int i=0;i<times;i++)
  {
  //write pwm value 2 to PIN 1,4
  analogWrite(1,2);
  analogWrite(4,2);
  delay(300);          
  //write pwm value 0 to PIN 1,4 
  analogWrite(1,0);
  analogWrite(4,0);
  delay(300);   
  }
}
