#ifndef graphics_H
#define graphics_H
#include "C12832_lcd.h" 


static char OneLine[] = {
0x80,   
    };

Bitmap bitmOneLine = {
  1, // XSize
  1, // YSize
  1, // Bytes in Line
  OneLine,  // Pointer to picture data 
};
static char TwoLine[] = {
0xc0,   
    };

Bitmap bitmTwoLine = {
  2, // XSize
  1, // YSize
  1, // Bytes in Line
  TwoLine,  // Pointer to picture data 
};
static char ThreeLine[] = {
0xe0,   
    };

Bitmap bitmThreeLine = {
  3, // XSize
  1, // YSize
  1, // Bytes in Line
  ThreeLine,  // Pointer to picture data 
};
static char FourLine[] = {
0xf0,   
    };

Bitmap bitmFourLine = {
  4, // XSize
  1, // YSize
  1, // Bytes in Line
  FourLine,  // Pointer to picture data 
};
static char FiveLine[] = {
0xf8,   
    };

Bitmap bitmFiveLine = {
  5, // XSize
  1, // YSize
  1, // Bytes in Line
  FiveLine,  // Pointer to picture data 
};
static char SixLine[] = {
0xfc,   
    };

Bitmap bitmSixLine = {
  6, // XSize
  1, // YSize
  1, // Bytes in Line
  SixLine,  // Pointer to picture data 
};
    
static char SevenLine[] = {
0xfe,   
    };

Bitmap bitmSevenLine = {
  7, // XSize
  1, // YSize
  1, // Bytes in Line
  SevenLine,  // Pointer to picture data 
};
    

#endif