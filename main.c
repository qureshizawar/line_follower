#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "delay.h"      /* calls delay parameters */
#include "pwm.h"
#include "adc.h"         //calls adc parameters
#include "camera.h"      // calls camera functions
#include "speed_control.h" // calls motor speed controls
#include "motor_controller.h" // calls motor speed controller
#include "collision.h"
#include "cases.h"



extern long tw;                     //defines delay time
extern unsigned char xl;            // defines number of black line pixels on the left
extern unsigned char xr;            // defines number of black line pixels on the right
extern int spdl;                    // defines speed of left motor
extern int spdr;                    // defines speed of right motor
extern unsigned char error;         // defines error for the controller
extern unsigned char lost;
extern unsigned char lf;
                                
void main(void) {                                                      
  
	EnableInterrupts;
  adc_initialise ();             //initialise the adc
  pwm_init();                    // inintialise pwm
  DDRM = 0x0d;                    //set port M to output
  tw = 650 ;                      // delay time between dummy and actual read for camera
  spdl = 255;                     // initial speed of left motor
  spdr = 255;                     // initial speed of right motor
  lf = 0;                         // initial value for left flag
                  

while (1)                                  
  {                                    
                                                                   
  
  dummy_read();                      //dummy read of camera to clear residual charge
  
  delay (tw);                        //delay to wait for charge to build up again
                              
 
       
  main_read();                       //main read from camera
   
   
  tw = max_read(tw);                  //adjust delay to get correct exposure
  
  line_locator();                     //function for locating the black line 
  
  corner_locator();                   //function for identifying corners
  
  lost_locator();                     //function for deciding if lost
  
  cross_locator();                    //function for detecting cross
  
  collision();                        //function for collision detection
  
  motor_controller();                 //function for the motor controller
  
  
  
    
  

  }
    
}