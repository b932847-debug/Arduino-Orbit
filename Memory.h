#pragma once
#include <Arduino.h>
void Memory_begin();
void Memory_add(const String &role,const String &text);
String Memory_recent(uint8_t count=5);
void Memory_clear();
