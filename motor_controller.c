#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "delay.h"
#include "pwm.h"
#include "camera.h"
#include "speed_control.h"
#include "motor_controller.h"
#include "cases.h"

unsigned char k; //defines proportional factor
unsigned char error;  // defines error for the controller
extern unsigned char xl; // defines number of black line pixels on the left
extern unsigned char xr; // defines number of black line pixels on the right
int spdl;       // assigning a veriable for type conversion
int spdr;       // assigning a veriable for type conversion
extern unsigned char lost;
extern unsigned char lf;
extern unsigned char cl;
extern unsigned char cr;
extern unsigned char cross;
unsigned char instructions[9] = {3,9,0,9,0,9,0,9,3};  //array of instructions that robot undertakes when arrives at crossroads  
unsigned char e;                                      //counter for loading instructions
extern unsigned char i;



void motor_controller(void)                           //function for motor controller
  {
  
 //if(e==8)
  //{
   //e = 0;
  //}
  
 if(cross == 1)                                       //if cross flag is 1 perform next instruction
  {
    i = instructions[e];
    cases(i);                                         //select instruction
    
    e++;                                              //increment e

   }
  
  else
    {
      
 
 
   if (lost == 0 )             //check if lost
    {
      
    
      k = 133/10;              //proportional gain for controller
     
      if(xl < xr)              //check if robot moving to the right of the line
        {
          error = (xr - xl);   //calculate error
          spdr = (255 - k*error); //turning according to proportional control
          spdl = 255;
          speed_control(spdl, spdr);
        }
      else
        {
          error = (xl - xr);   //calculate error
          spdl = (255 - k*error); //turning according to proportional control
          spdr = 255;
          speed_control(spdl, spdr);
        }

    } 
    
    else
      {
        
      if(lf == 1)            //corner detected turn left
        {
          
            spdl = 255;
            spdr = -255;
            speed_control(spdl, spdr);
          
        }
        else                 //corner detected turn right
          {
          spdl = 255;
          spdr = -255;
          speed_control(spdl, spdr);
          } 
       
      }
    }
      
  }
      
    