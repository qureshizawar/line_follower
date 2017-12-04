#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include  "adc.h"

unsigned char x;

void adc_initialise (void)

  {
    ATD0CTL2_ADPU = 1; // powering up the ATD
    ATD0CTL3 = 0x08;    // selecting one conversion per sequence
    ATD0CTL4 = 0xc0; // selecting 8 bit resolution  
  }

void adc_convert (void)

  {
   ATD0CTL5 = 0x00; // clearing residual charge 
   ATD0CTL5 = 0x00; // selecting one channel,setting analogue input channel to AN0 and starting sequence
  }
  
void adc_collision_left(void)
  {
    ATD0CTL5 = 0x01; // clearing residual charge  
    ATD0CTL5 = 0x01; // selecting one channel,setting analogue input channel to AN0 and starting sequence
  }
  
  void adc_collision_right(void)
  {
    ATD0CTL5 = 0x02; // clearing residual charge  
    ATD0CTL5 = 0x02; // selecting one channel,setting analogue input channel to AN0 and starting sequence
  }
  
unsigned char adc_read (void)          

  {
  while (ATD0STAT0_SCF == 0)          //wait until completion of conversion process (SCF is flag from ATD status register)
    {}
    x = ATD0DR0H;                        //read the output of ADC
    return x;
  }
  