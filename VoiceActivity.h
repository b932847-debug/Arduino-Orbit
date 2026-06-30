#pragma once
enum VoiceState{
  VOICE_SILENT,
  VOICE_LISTENING,
  VOICE_SPEAKING
};

VoiceState Voice_currentState();
