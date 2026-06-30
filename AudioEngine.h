#pragma once
#include <Arduino.h>
enum SoundEffect{SOUND_BOOT,SOUND_CLICK,SOUND_NOTIFY,SOUND_ERROR};
void Audio_begin();
void Audio_play(SoundEffect);
void Audio_setVolume(uint8_t);
uint8_t Audio_getVolume();
void Audio_update();
