#pragma once
#include <Arduino.h>

void Personality_begin();

void Personality_setName(const String &name);
String Personality_getName();

void Personality_setMood(const String &mood);
String Personality_getMood();

String Personality_buildSystemPrompt();
