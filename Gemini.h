#pragma once
#include <Arduino.h>

void Gemini_begin();
String Gemini_generate(const String &prompt);
void Gemini_update();
