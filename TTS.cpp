#include "TTS.h"
#include "OrbRenderer.h"
#include "ChatRenderer.h"

#include <Arduino.h>

static bool speaking = false;
static String lastText = "";

void TTS_begin()
{
    speaking = false;
    lastText = "";
}

void TTS_speak(const String &text)
{
    lastText = text;
    speaking = true;

    Orb_setState(ORB_SPEAKING);
    Chat_addMessage(text, CHAT_ORBIT);

    // TODO:
    // Send text to your selected TTS provider.
    // Supported future backends:
    //  - OpenAI TTS
    //  - Piper
    //  - Google Cloud TTS
    //  - ElevenLabs
    //  - Azure Speech
    //
    // When audio playback starts, keep speaking=true.
    // When playback finishes, call TTS_finished().
}

void TTS_finished()
{
    speaking = false;
    Orb_setState(ORB_IDLE);
}

bool TTS_isSpeaking()
{
    return speaking;
}

String TTS_lastMessage()
{
    return lastText;
}

void TTS_update()
{
    // Placeholder for future streaming playback state.
}
