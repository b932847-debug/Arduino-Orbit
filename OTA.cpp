#include "OTA.h"

static bool ready=false;

void OTA_begin(const char* hostname){
    (void)hostname;
    // Placeholder:
    // Integrate ArduinoOTA or ElegantOTA here.
    ready=true;
}

void OTA_update(){
    // Call ArduinoOTA.handle() here in the future.
}

bool OTA_ready(){
    return ready;
}
