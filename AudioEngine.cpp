#include "AudioEngine.h"
static uint8_t volume=80;
void Audio_begin(){}
void Audio_play(SoundEffect effect){
 switch(effect){
 case SOUND_BOOT: break;
 case SOUND_CLICK: break;
 case SOUND_NOTIFY: break;
 case SOUND_ERROR: break;
 }
}
void Audio_setVolume(uint8_t v){volume=v;}
uint8_t Audio_getVolume(){return volume;}
void Audio_update(){}
