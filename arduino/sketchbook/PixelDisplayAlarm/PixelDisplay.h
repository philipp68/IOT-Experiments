/*
  PixelDisplay.h - Library for LED pixel display.
*/
#ifndef PixelDisplay_h
#define PixelDisplay_h

#include "Arduino.h"
#include "FastLED.h"       // Fastled library to control the LEDs
#include "ProgMemImages.h"

// How many leds are connected?
#define NUM_LEDS 256

// Define the Data Pin
#define DATA_PIN 3  // Connected to the data pin of the first LED strip

class PixelDisplay
{
  public:
    static void setup() {
      static CRGB leds[NUM_LEDS];
      FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // Init of the Fastled library
      FastLED.setBrightness(50);
    }
    
    static void clear()
    {
      FastLED.clear();
    }

    static void show()
    {
      FastLED.show();
    }
    
    static void setBrightness(int brightness)
    {
      if(brightness < 0 || brightness > 255) {
       return;
      }
      FastLED.setBrightness(brightness);
    }
    
    static void setPixel(int x, int y, CRGB color)
    {
      if(x>15 || x<0 || y>15 || y<0) {
        return; 
      }
      CRGB *arr= FastLED.leds();
      int xReversed = 15-x;
      arr[ PixelDisplay::XY(xReversed,y) ] = color;
    }
    
    static void printColon(int x, int y, CRGB color, CRGB backgroundColor)
    {
      printChar(x, y, color, backgroundColor, Colon, false);  
    }
    
    static void printSingleDigit(int x, int y, int number, CRGB color, CRGB backgroundColor, boolean clearBackground)
    {
      if(number > 10 || number < 0) {
        return;
      }
      
      switch(number) {
        case 0 : 
          printChar(x,y,color, backgroundColor, Zero, clearBackground);  
        break;
        case 1 : 
          printChar(x,y,color, backgroundColor, One, clearBackground);  
        break;
        case 2 :
          printChar(x,y,color, backgroundColor, Two, clearBackground);  
        break;
        case 3 :
          printChar(x,y,color, backgroundColor, Three, clearBackground);  
        break;
        case 4 :
          printChar(x,y,color, backgroundColor, Four, clearBackground);  
        break;
        case 5 :
          printChar(x,y,color, backgroundColor, Five, clearBackground);  
        break;
        case 6 :
          printChar(x,y,color, backgroundColor, Six, clearBackground);  
        break;
        case 7 :
          printChar(x,y,color, backgroundColor, Seven, clearBackground);  
        break;
        case 8 :
          printChar(x,y,color, backgroundColor, Eight, clearBackground);  
        break;
        case 9 :
          printChar(x,y,color, backgroundColor, Nine, clearBackground);  
        break;
       } 
    }

    static void setImgFromProgmem(long img[])
    {  
      CRGB *arr= FastLED.leds();
      for(int i = 0; i < NUM_LEDS; i++) {
        arr[i] = pgm_read_dword(&(img[i]));
      }
    }
    
  private:  
    static uint16_t XY( uint8_t x, uint8_t y)
    {
      uint16_t i;
      
      if( _matrixSerpentineLayout == false) {
        i = (y * _width) + x;
      }
    
      if( _matrixSerpentineLayout == true) {
        if( y & 0x01) {
          // Odd rows run backwards
          uint8_t reverseX = (_width - 1) - x;
          i = (y * _width) + reverseX;
        } else {
          // Even rows run forwards
          i = (y * _width) + x;
        }
      }
      
      return i;
    }
    
    static void printChar(int x, int y, CRGB color, CRGB backgroundColor, uint8_t number[], boolean clearBackground)
    {
      uint8_t width = 3;
      uint8_t height = 5;
    
      uint8_t arr[15];
      for(int i = 0; i < width*height; i++) {
        arr[i] = pgm_read_dword(&(number[i]));
      }
    
      for(uint8_t p=0;p<width*height;p++)
      {
        uint8_t xOffset = x + p%3;
        uint8_t yOffset = y + p/width;
        if(arr[p] == 1) {  
          setPixel(xOffset,yOffset,color);
        } else if (clearBackground == true) {
          setPixel(xOffset,yOffset,backgroundColor);
        }
      }
    }

    static const uint8_t _width = 16;
    static const uint8_t _height = 16; 
    static const bool _matrixSerpentineLayout = true; // Param for different pixel layouts
};

#endif

