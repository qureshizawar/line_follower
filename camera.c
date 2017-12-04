#include <hidef.h>      //common defines and macros 
#include "derivative.h"      //derivative-specific definitions
#include "delay.h"       //calls delay parameters 
#include "adc.h"         //calls adc parameters
#include "camera.h"


unsigned char t;            //defines counter
long tw;                     //defines delay time
unsigned char r;              //read from adc
unsigned char a;             //counter for data array
unsigned char data[64];        //data array
unsigned char max;             //maximum value from data array
unsigned char Ulimit;          //upper limit for max value
unsigned char Blimit;          //lower limit for max value
unsigned char index[64];       //array for storing
unsigned char xl;              // defines number of black line pixels on the left
unsigned char xr;              // defines number of black line pixels on the right
unsigned char lost;            //defines lost flag
unsigned char y;                //not black pixel counter
unsigned char lf;               //turn flag
unsigned char cross;            //crossroad flag       


void dummy_read(void)                 //dummy read function
  {
  
    t = 0;                   //reset counter for read pulses
    
   PTM_PTM2 = 1;             //set SI to high
   PTM_PTM3 = 1;             //set clock to high
   PTM_PTM2 = 0;             //set SI to low
   PTM_PTM3 = 0;             //set clock to low                             
    while ( t < 64)                   //counting 65 clock pulses
    {
          

      adc_convert();                  //convert camera value to digital value
      r = adc_read();                 //read adc value
      PTM_PTM3 = 1;                  //set clock to high
      PTM_PTM3 = 0;                   //set clock to low
      t++;                            //add 1 to counter
    }
  }
  
void main_read(void)                  //main read function
  {
   t = 0;                    //reset counter for read pulses
   a = 0;                    //initial data array counter value
   
   PTM_PTM2 = 1;             //set SI to high
   PTM_PTM3 = 1;             //set clock to high
   PTM_PTM2 = 0;             //set SI to low
   PTM_PTM3 = 0;             //set clock to low                        
    while ( t < 64)                   //counting 65 clock pulses
    {

     
      adc_convert();                  //convert camera value to digital value
      r = adc_read();                 //read adc value
      data[a] = r;                    //store adc value in array
      PTM_PTM3 = 1;                  //set clock to high
      PTM_PTM3 = 0;                   //set clock to low
      t++;                            //add 1 to counter
      a++;                            //add 1 to data array counter
    }
  }
long max_read(long tw)                //adjusting delay
  {
  
	 Ulimit = 175;                      //setting upper limit of max
	 Blimit = 160;                      //setting lower limit of max
  
   max = data[0];                     //finding maximum value from data array
 
  for (t = 0; t < 64; t++)
  {
    if (data[t] > max)
    {
       max  = data[t];
    }
  }
 
      if(max > Ulimit)                   //decreasing delay if max greater than chosen upper limit
      {
        tw = tw*9/10;                   //incremently decrease delay
        if (tw==0)                      //if tw equal to 0 set tw to 1, cant have a delay = 0
          {
            tw = 1;
          }
      }
      
     if(max < Blimit)                     //increasing  delay if max smaller than chosen lower limit
      {
        tw = tw*11/10;                    //incremently increase delay
        if (tw < 10)                      //if tw less than 10, increment tw by 1
          {
            tw++;
          }
      }
     
     return tw;                           //output tw

  
  }
 
 void line_locator(void)                  //function for locating the black line
  {
    xl = 0;                               //initial value for number of black pixels on the left
    xr = 0;                               //initial value for number of black pixels on the right
    
  
    for (t = 0; t < 64; t++)              //extracting black pixels from camera output
    {
      if (data[t] < 100)
      {
        
         if (t <= 31)                     //finding black pixels on the right
          {
          xr++;                           //counting number of black pixels on the right
          } 
         if (t > 31)                      //finding black pixels on the left
          {
          xl++;                           //counting number of black pixels on the left
          }
        
      }
        
                                                      
    }
    
   
  }
  
  
void corner_locator(void)                //function for finding corners
  {
  
   if((data[0]) < 100)                   //set left flag to zero when the right most pixel is black (turn complete)
    {
    lf = 0;
    }
   if ((data[63]) < 100)                 //set left flag to one when the left most pixel is black
    {
     lf = 1;
    }
  }
  
  
  
void lost_locator(void)                   //function to indictate if robot is lost
  {
    for (t = 0; t < 64; t++)               //counter
      {
        if (data[t] > 100)                 //checking if each pixel is not black
          {
            y++;                           //increment y if pixel is not black
          }
      }
        
     if (y == 64)                          //if all pixels are counted as not black raise lost flag
      {
        lost = 1;
      }
     else
      {
        lost = 0;
      }
      
      y = 0; 
  }

void cross_locator(void)                    // function to indicate if robot at crossroads
  {
    if(data[0] < 100 && data[63] < 100)      //check if both left and right hand most bits are black
      {
        cross = 1;                          //set cross flag to 1 if condition above true
      }
      
      else
        {
          cross =0;                           //leave cross flag as 0 if not at crossroads
        }
  }

      
    
  