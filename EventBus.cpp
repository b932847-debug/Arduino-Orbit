#include "EventBus.h"
static OrbitEvent last=EVT_WIFI_CONNECTED;
void Event_emit(OrbitEvent e){last=e;}
OrbitEvent Event_last(){return last;}
