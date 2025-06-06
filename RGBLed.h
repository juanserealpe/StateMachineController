#ifndef RGBLed_H
#define RGBLed_H

#define PIN_RED 8
#define PIN_GREEN 9
#define PIN_BLUE 10

void StartRGB();
void  OffRGB();

void ShowRGB(unsigned char red, unsigned char green, unsigned char blue);
void ShowRed();
void ShowGreen();
void ShowBlue();

#endif