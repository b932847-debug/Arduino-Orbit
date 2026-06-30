#include "Gemini.h"
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

extern const char* GEMINI_API_KEY;
extern const char* AI_ENDPOINT;

void Gemini_begin(){}

String Gemini_generate(const String &prompt)
{
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;

    String url=String(AI_ENDPOINT)+"?key="+String(GEMINI_API_KEY);

    if(!http.begin(client,url))
        return "HTTP begin failed.";

    http.addHeader("Content-Type","application/json");

    DynamicJsonDocument request(512);

    JsonArray contents=request.createNestedArray("contents");
    JsonObject content=contents.createNestedObject();
    JsonArray parts=content.createNestedArray("parts");
    parts.createNestedObject()["text"]=prompt;

    String body;
    serializeJson(request,body);

    int code=http.POST(body);

    if(code<=0){
        http.end();
        return "Gemini Offline";
    }

    String response=http.getString();
    http.end();

    DynamicJsonDocument doc(16384);

    if(deserializeJson(doc,response))
        return "JSON Parse Error";

    return doc["candidates"][0]["content"]["parts"][0]["text"].as<String>();
}

void Gemini_update(){}
