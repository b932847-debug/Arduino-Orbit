#include "Context.h"
#include "Personality.h"
#include "Memory.h"

static int batteryPercent=100;
static bool wifiConnected=false;
static String currentTime="Unknown";

void Context_begin(){}

void Context_setBattery(int percent){batteryPercent=percent;}
void Context_setWiFi(bool connected){wifiConnected=connected;}
void Context_setTime(const String &timeText){currentTime=timeText;}

String Context_build(const String &userPrompt)
{
    String ctx;

    ctx += Personality_buildSystemPrompt();
    ctx += "\n\n";

    ctx += "Device Status\n";
    ctx += "Battery: " + String(batteryPercent) + "%\n";
    ctx += "WiFi: ";
    ctx += wifiConnected ? "Connected\n" : "Disconnected\n";
    ctx += "Time: " + currentTime + "\n\n";

    ctx += "Recent Conversation:\n";
    ctx += Memory_recent(5);
    ctx += "\nUser:\n";
    ctx += userPrompt;

    return ctx;
}
