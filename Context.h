#pragma once
#include <Arduino.h>

void Context_begin();
void Context_setBattery(int percent);
void Context_setWiFi(bool connected);
void Context_setTime(const String &timeText);
String Context_build(const String &userPrompt);
