
#include "WakeWord.h"
#include "Speech.h"
#include "OrbRenderer.h"
#include "ChatRenderer.h"

#include <Arduino.h>

static bool enabled = true;
static bool detected = false;
static unsigned long lastTrigger = 0;
static const unsigned long COOLDOWN_MS = 3000;

void WakeWord_begin()
{
    enabled = true;
    detected = false;
}

void WakeWord_setEnabled(bool state)
{
    enabled = state;
}

bool WakeWord_isEnabled()
{
    return enabled;
}

bool WakeWord_detected()
{
    return detected;
}

void WakeWord_trigger()
{
    if(!enabled)
        return;

    unsigned long now = millis();

    if(now - lastTrigger < COOLDOWN_MS)
        return;

    lastTrigger = now;
    detected = true;

    Orb_setState(ORB_LISTENING);
    Chat_showThinking();
    Speech_startListening();
}

void WakeWord_clear()
{
    detected = false;
}

void WakeWord_update()
{
    // Placeholder:
    // Integrate Porcupine, Vosk, Whisper streaming,
    // or another wake-word engine here.
    // When a wake word is recognized:
    //
    // WakeWord_trigger();
}
