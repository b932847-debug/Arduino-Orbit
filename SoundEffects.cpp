#include "SoundEffects.h"
#include "AudioEngine.h"
void Sound_play(OrbitSound s){switch(s){case SOUND_BOOT:Audio_playStartup();break;case SOUND_NOTIFY:case SOUND_SUCCESS:Audio_playNotification();break;case SOUND_ERROR:Audio_playError();break;default:break;}}