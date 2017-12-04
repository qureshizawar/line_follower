#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "delay.h"      /* calls delay parameters */
#include "pwm.h"
#include "adc.h"         //calls adc parameters
#include "camera.h"      // calls camera functions
#include "speed_control.h" // calls motor speed controls
#include "motor_controller.h" // calls motor speed controller
#include "collision.h"


unsigned char cl;            //output from left light sensor
unsigned char cr;            //output from right light sensor
extern int spdl;
extern int spdr;







void collision(void)     //function for collision detection
  {
  
  adc_collision_left();        //initialise left collision sensor
  
  cl = adc_read();             //read the value of left collision sensor from adc
  
  adc_collision_right();       //initialise right collision sensor
  
  cr = adc_read();             //read the value of right collision sensor from adc
  
  
  if (cr > 79)                       //sensitivity of light sensors only checking right sensor as left is broken
  {
    spdl = -255;                     //set left wheel at max reverse speed
    spdr = -255;                      //set right wheel at max reverse speed
    
    speed_control(spdl, spdr);       //set speed of motors to given speeds
    
    delay(50000);                     //wait for robot to move backwards
  
    spdl = 255;                       //set left speed of motor for turning right
    spdr = -255;                       //set right speed of motor for turning right
    
    speed_control(spdl, spdr);         //set speed of motors for turning right
    
    delay(90000);                      //wait for robot to turn 180 degrees
  }
  

  
    
  }