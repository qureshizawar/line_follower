#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "delay.h"      /* delay location */

void delay (long t) 
  {
    long x;
    for( x = t; x>0; x--);
  }