#pragma once
enum OrbitEvent{
 EVT_WIFI_CONNECTED,
 EVT_AI_REQUEST,
 EVT_AI_RESPONSE,
 EVT_MIC_ACTIVITY,
 EVT_SLEEP
};
void Event_emit(OrbitEvent e);
OrbitEvent Event_last();
