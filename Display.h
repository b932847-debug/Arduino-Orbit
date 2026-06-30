#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "DisplayTypes.h"

void Display_begin();
void Display_update();

void Display_setPage(DisplayPage page);
DisplayPage Display_getPage();

void Display_clear();
void Display_setBackground(uint16_t color);
void Display_setTextColor(uint16_t color);

Adafruit_ST7789 &Display_getTFT();