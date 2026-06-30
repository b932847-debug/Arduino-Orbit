#pragma once
enum OrbitState{
 STATE_BOOT,
 STATE_CONNECTING_WIFI,
 STATE_IDLE,
 STATE_LISTENING,
 STATE_THINKING,
 STATE_SPEAKING,
 STATE_ERROR,
 STATE_SLEEP
};
void System_begin();
void System_setState(OrbitState s);
OrbitState System_getState();
void System_update();
