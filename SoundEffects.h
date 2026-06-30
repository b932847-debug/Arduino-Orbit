#pragma once
enum OrbitSound{
 SOUND_BOOT,
 SOUND_NOTIFY,
 SOUND_SUCCESS,
 SOUND_ERROR,
 SOUND_LISTEN,
 SOUND_THINK
};
void Sound_play(OrbitSound s);
