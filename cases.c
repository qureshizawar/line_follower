#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "delay.h"
#include "pwm.h"
#include "camera.h"
#include "speed_control.h"
#include "motor_controller.h"
#include "cases.h"

extern int spdl;                    // defines speed of left motor
extern int spdr;                    // defines speed of right motor
extern unsigned char lf;
unsigned char i;                      

void cases(unsigned char i)          //define function for library of different instructions
  {
    switch(i)                              //switch function to choose which instruction to undertake
  {
    case 3:                                //right hand turn case
    
    spdl = 255;                            //set motor speeds
    spdr = 255;
    speed_control(spdl, spdr);
    delay(15000);                          //delay for robot to overshoot crossroad
    spdl = 255;                             
    spdr = -255;
    lf = 1;                                //set turn flag to one, so robot keeps turning right
    speed_control(spdl, spdr);         
    delay(40000);                           //wait for robot to turn so line follower can take over
    
    break;
  
    case 9:                                 //left hand turn case
  
    spdl = 255;                              //set motor speeds
    spdr = 255;
    speed_control(spdl, spdr);
    delay(15000);                           //delay for robot to overshoot crossroad
    spdl = -255;                           
    spdr = 255;
    lf = 0;                                 //set turn flag to zero, so robot keeps turning left
    speed_control(spdl, spdr);
    delay(40000);                            //wait for robot to turn so line follower can take over
    
    break;
    
    case 0:                                   //straight line case, ignore crossroad
  
    spdl = 255;                                //set motor speeds
    spdr = 255;
    speed_control(spdl, spdr);
    delay(50000);                             //delay so robot crosses crossroad
    
    break;
    
  }
  
  }

