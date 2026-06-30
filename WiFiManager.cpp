#include "WiFiManager.h"
#include <WiFi.h>

static const char* s="";
static const char* p="";

void WiFiManager_begin(const char* ssid,const char* password){
    s=ssid; p=password;
    WiFi.begin(s,p);
}

void WiFiManager_update(){
    if(WiFi.status()!=WL_CONNECTED)
        WiFi.reconnect();
}

bool WiFiManager_connected(){
    return WiFi.status()==WL_CONNECTED;
}

String WiFiManager_ip(){
    return WiFi.localIP().toString();
}

void WiFiManager_reconnect(){
    WiFi.disconnect();
    WiFi.begin(s,p);
}
