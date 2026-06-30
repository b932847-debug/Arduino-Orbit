#include "Settings.h"
static uint8_t volume=80,brightness=100; static bool wake=true;
void Settings_begin(){Settings_load();}
void Settings_load(){}
void Settings_save(){}
void Settings_factoryReset(){volume=80;brightness=100;wake=true;}
uint8_t Settings_getVolume(){return volume;}
void Settings_setVolume(uint8_t v){volume=v;}
uint8_t Settings_getBrightness(){return brightness;}
void Settings_setBrightness(uint8_t b){brightness=b;}
bool Settings_wakeWordEnabled(){return wake;}
void Settings_enableWakeWord(bool e){wake=e;}
