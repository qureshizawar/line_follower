#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include  "pwm.h"
#include  "speed_control.h"

unsigned char spdlc;       // assigning a veriable for type conversion
unsigned char spdrc;       // assigning a veriable for type conversion

void speed_control (int spdl, int spdr)  // function for controling speeds of the motors
  {

   if (spdl > 0)
      {
      PTT_PTT7 = 1;    // setting the direction register(forward) for left motor
      }
   else
      {
      PTT_PTT7 = 0;    // setting the direction register(backward) for left motor
      }
      

  
   if (spdl < 0)
    {
      spdl = -spdl;    // changing negetive values to positive
    }
    
  
    if (spdl > 255)
    {
      spdl = 255;      // limitting input to left motor
    }
    

    spdlc = (unsigned char)(spdl);  // converting int value to unsigned char
  
    PWMDTY1 = spdlc;    // setting left motor speed by setting the duty of the PWM to the left motor
    

    if (spdr > 0)
      {
      PTT_PTT6 = 1;    // setting the direction register(forward) for right motor
      }
    else
      {
      PTT_PTT6 = 0;    // setting the direction register(backward) for right motor
      }
      
    
        
     if (spdr < 0)
      {
      spdr = -spdr;     // changing negetive values to positive
      }
      
      
     if (spdr > 255)
      {
      spdr = 255;      // limitting input to right motor
      }
    

     spdrc = (unsigned char)spdr;    // converting int value to unsigned char
     
    PWMDTY0 = spdrc;    // setting right motor speed by setting the duty of the PWM to the right motor
  
  }