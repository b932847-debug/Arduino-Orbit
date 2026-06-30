#pragma once
#include <Arduino.h>
void Battery_begin(uint8_t analogPin);
void Battery_update();
float Battery_voltage();
int Battery_percent();
bool Battery_isCharging();
