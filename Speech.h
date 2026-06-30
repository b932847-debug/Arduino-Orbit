#pragma once

#include <Arduino.h>

// Initialize the speech subsystem
void Speech_begin();

// Start/stop listening state
void Speech_startListening();
void Speech_stopListening();

// Query current listening state
bool Speech_isListening();

// Store/retrieve partial recognition text
void Speech_setPartial(const String &text);
String Speech_getPartial();

// Update the speech engine.
// This is intended to be called every loop().
void Speech_update();
