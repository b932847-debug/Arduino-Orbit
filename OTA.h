#pragma once
#include <Arduino.h>

void OTA_begin(const char* hostname="Orbit");
void OTA_update();
bool OTA_ready();
