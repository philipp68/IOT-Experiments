//Demo for 4-Digit Display (D4056A) only by Catalex
//Hardware: A 4-Digit Display (D4056A) 
//Board: Catduino or Arduino UNO R3,Arduino Mega2560...
//IDE:   Arduino-1.0
//Function: Display the decimals on the digital tube.
//Store: http://www.aliexpress.com/store/1199788
//          http://dx.com
/*********************************************************************/

#include "TM1637.h"
#define CLK A5//connect CLK of the 4-Digit Display to A5 of Arduino and can be changed to other ports    
#define DIO A4//
TM1637 disp(CLK,DIO);
void setup()
{
  disp.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  disp.init(D4056A);//D4056A is the type of the module
}
void loop()
{
  disp.display(0.999);
  delay(1000);
  disp.display(999);
  delay(1000);
  disp.display(-0.99);
  delay(1000);
  disp.display(999.9);
  delay(1000);
  disp.display(9999);
  delay(1000);
  disp.display(-9.99);
  delay(1000);
  disp.display(0.9);
  delay(1000);
}

