#pragma once

#include <Arduino.h>

// Initialize the text-to-speech subsystem.
void TTS_begin();

// Speak the supplied text.
void TTS_speak(const String &text);

// Notify the subsystem that playback has finished.
void TTS_finished();

// Returns true while Orbit is speaking.
bool TTS_isSpeaking();

// Returns the last text sent to TTS.
String TTS_lastMessage();

// Update the TTS subsystem.
// Call once every loop().
void TTS_update();
