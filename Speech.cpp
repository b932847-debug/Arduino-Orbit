
#include "Speech.h"
#include "ChatRenderer.h"
#include "OrbRenderer.h"

static bool listening = false;
static String partialText = "";

void Speech_begin()
{
    listening = false;
    partialText = "";
}

void Speech_startListening()
{
    listening = true;
    Orb_setState(ORB_LISTENING);
    Chat_showThinking();
}

void Speech_stopListening()
{
    listening = false;
    Orb_setState(ORB_IDLE);
}

bool Speech_isListening()
{
    return listening;
}

void Speech_setPartial(const String &text)
{
    partialText = text;
}

String Speech_getPartial()
{
    return partialText;
}

void Speech_update()
{
    // Placeholder for future speech recognition integration.
    // Suggested engines:
    //  - Vosk (local)
    //  - Whisper API (cloud)
    //  - Google Speech-to-Text
}
