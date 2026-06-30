#pragma once
#include <Arduino.h>

enum OrbState{
  ORB_IDLE,
  ORB_LISTENING,
  ORB_THINKING,
  ORB_SPEAKING,
  ORB_SLEEP,
  ORB_ERROR
};

void Orb_begin();
void Orb_setState(OrbState state);
void Orb_update();
void Orb_draw(int x,int y);
