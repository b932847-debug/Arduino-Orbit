#pragma once
#include <Arduino.h>

void AI_begin();
String AI_ask(const String &prompt);
bool AI_isBusy();
void AI_update();
