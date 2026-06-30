#include "SystemState.h"
static OrbitState current=STATE_BOOT;
void System_begin(){}
void System_setState(OrbitState s){current=s;}
OrbitState System_getState(){return current;}
void System_update(){}
