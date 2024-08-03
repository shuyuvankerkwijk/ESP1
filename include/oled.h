#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

// functions
void oledSetup();
void oledDisplay(String message);
void oledAppendDisplay(String message);

#endif // OLED_H