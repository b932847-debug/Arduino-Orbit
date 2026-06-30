#include "VoiceActivity.h"
#include "WaveRenderer.h"
VoiceState Voice_currentState(){return Wave_voiceDetected()?VOICE_LISTENING:VOICE_SILENT;}
