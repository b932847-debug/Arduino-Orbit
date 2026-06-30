#pragma once

#include <Arduino.h>

// Initialize the wake-word subsystem
void WakeWord_begin();

// Enable or disable wake-word detection
void WakeWord_setEnabled(bool state);
bool WakeWord_isEnabled();

// Update the wake-word engine.
// Call this once every loop().
void WakeWord_update();

// Trigger the wake-word manually.
// Useful for testing or future integrations.
void WakeWord_trigger();

// Returns true if a wake word has been detected.
bool WakeWord_detected();

// Clears the detection flag after handling.
void WakeWord_clear();
