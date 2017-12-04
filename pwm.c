#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include  "pwm.h"


void pwm_init(void)
  {
    PWMCLK_PCLK0 = 1;   // setting clock SA as the clock source for PWM channel 0
    PWMPRCLK =0x02;     // setting the clock rate of clk A
    PWMSCLA = 0x01;     // setting the clk rate of clk SA
    PWMCAE_CAE0 = 1;    // setting channel 0 to centre align output mode
    PWMPER0 = 0xFF;     // setting channel period to 510*(period clk SA) 
    PWMPOL_PPOL0 = 1;   // setting the polarity of channel 0 to high at beginning of period
    PWME_PWME0 = 1;     // enabling the PWM register to channel 0
    DDRT_DDRT6 = 1;     // settting register for right motor to input
    
    PWMCLK_PCLK1 = 1;   // setting clock SA as the clock source for PWM channel 1
    PWMPRCLK =0x02;     // setting the clock rate of clk A
    PWMSCLA = 0x01;     // setting the clk rate of clk SA
    PWMCAE_CAE1 = 1;    // setting channel 1 to centre align output mode
    PWMPER1 = 0xFF;     // setting channel period to 510*(period clk SA) 
    PWMPOL_PPOL1 = 1;   // setting the polarity of channel 1 to high at beginning of period
    PWME_PWME1 = 1;     // enabling the PWM register to channel 1
    DDRT_DDRT7 = 1;     // settting register for left motor to input
  
  }
