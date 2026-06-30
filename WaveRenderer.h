#pragma once

#include <Arduino.h>

void Wave_begin(uint8_t micPin = 34);

void Wave_update();

void Wave_draw(int x, int y, int width, int height);

int Wave_level();

bool Wave_voiceDetected();