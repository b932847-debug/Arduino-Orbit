#include <WiFi.h>
#include <Display.h> 
#include <BootScreen.h>
#include <Transition.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "Morse.h"
#include "OrbitData.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <OrbRenderer.h>
#include <WaveRenderer.h>
#include <ChatRenderer.h>
 #include <TypingEffect.h>
#include <SystemState.h>
#include <TaskScheduler.h>
#include <EventBus.h>
#include <AudioEngine.h>
 #include <SoundEffects.h> 
 #include <TTS.h>
const char* WIFI_SSID="";
const char* WIFI_PASSWORD="";
const char* GEMINI_API_KEY = "";

const char* AI_ENDPOINT =
"https://generativelanguage.googleapis.com/v1beta/models/gemini-3.5-flash:generateContent";


String mood="Curious";
#define TFT_CS 5
#define TFT_DC 27
#define TFT_RST 4

#define MIC_PIN 34
Adafruit_ST7789 tft(TFT_CS,TFT_DC,TFT_RST);
// Display owned by Display.cpp
bool aiThinking = false;
void initDisplay(){

    tft.init(240,320);

    tft.setRotation(0);

    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(ST77XX_CYAN);

    tft.setTextSize(2);

    tft.setCursor(20,40);

    tft.println("ORBIT");

    tft.setTextSize(1);

    tft.println();

    tft.println("Booting...");

    delay(1500);

    tft.fillScreen(ST77XX_BLACK);
}
void connectWiFi(){
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("Connecting WiFi");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.status());
Serial.println(WiFi.localIP());
tft.fillScreen(ST77XX_BLACK);

tft.setCursor(20,20);

tft.println("WiFi Connected");

delay(1000);
}
String askCloud(String prompt) {

  if (WiFi.status() != WL_CONNECTED) {
    return "WiFi disconnected.";
  }

WiFiClientSecure client;
client.setInsecure();


  HTTPClient http;

  String url =
    String(AI_ENDPOINT) +
    "?key=" +
    String(GEMINI_API_KEY);



  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
DynamicJsonDocument request(512);

JsonArray contents = request.createNestedArray("contents");
JsonObject content = contents.createNestedObject();
JsonArray parts = content.createNestedArray("parts");
JsonObject part = parts.createNestedObject();

part["text"] = prompt;

String body;
serializeJson(request, body);

// Optional: print the JSON to Serial for debugging



  int code = http.POST(body);

  if (code <= 0) {
    Serial.print("HTTP Error: ");
    Serial.println(code);
    Serial.println(http.errorToString(code));
    http.end();
    return "Gemini Offline";
  }

  String response = http.getString();
  http.end();





DynamicJsonDocument responseDoc(16384);

if (deserializeJson(responseDoc, response)) {
    return "JSON Parse Error";
}

if (responseDoc["candidates"].isNull()) {
    return response;
}

return responseDoc["candidates"][0]["content"]["parts"][0]["text"].as<String>();
}
void showThinking(){

    aiThinking=true;

    tft.fillScreen(ST77XX_BLACK);

    tft.setCursor(25,50);

    tft.setTextSize(2);

    tft.println("Thinking...");

    tft.drawRoundRect(40,120,60,60,10,ST77XX_CYAN);

    tft.drawRoundRect(140,120,60,60,10,ST77XX_CYAN);

}

void showReply(String text){

    aiThinking=false;

    tft.fillScreen(ST77XX_BLACK);

    tft.drawRoundRect(8,165,224,145,8,ST77XX_WHITE);

    tft.setCursor(16,180);

    tft.setTextColor(ST77XX_WHITE);

    tft.setTextSize(1);

    tft.println(text);

}
void reply(String msg){
  Serial.println(""+msg);
  showReply(msg);
 
  flashMorse(msg);
}

void handleCommand(String cmd) {

    cmd.trim();
    if (cmd.length() == 0) return;

    String lower = cmd;
    lower.toLowerCase();

    // Show user's message
    Chat_addMessage(cmd, CHAT_USER);

    // Built-in commands
    if (lower == "hello") {
        reply("Hi QUADUL8R!");
        return;
    }

    if (lower == "status") {
        reply("Systems nominal.");
        return;
    }

    if (lower == "mood") {
        reply("Current mood: " + mood);
        return;
    }

    if (lower == "joke") {
        reply(jokes[random(jokeCount)]);
        return;
    }

    if (lower == "mission") {
        reply(missions[random(missionCount)]);
        return;
    }

    if (lower == "help") {
        reply("Ask me anything!");
        return;
    }

    // ===== AI =====

    System_setState(STATE_THINKING);
    Event_emit(EVT_AI_REQUEST);
    Orb_setState(ORB_THINKING);

    Chat_showThinking();

    String answer = askCloud(cmd);

    Typing_print(answer);

    reply(answer);

    Sound_play(SOUND_NOTIFY);

    Event_emit(EVT_AI_RESPONSE);

    System_setState(STATE_IDLE);
    Orb_setState(ORB_IDLE);

    // Future:
    // TTS_speak(answer);
}
tft.print("_");
void setup(){
  Serial.begin(115200);
// initDisplay(); // replaced by Display_begin();
  pinMode(LED_PIN,OUTPUT);
  randomSeed(micros());
  mood=moods[random(moodCount)];
  connectWiFi();
  reply("Orbit online.");

Display_begin();
 BootScreen_begin();

 BootScreen_draw("Starting...",10);

BootScreen_draw("Connecting WiFi...",40);

BootScreen_draw("Connecting Gemini...",80);

 BootScreen_draw("Ready!",100);
Orb_begin();
Chat_begin();
System_begin(); 
Scheduler_begin();
Audio_begin(); 
TTS_begin();
Sound_play(SOUND_BOOT);

}

void loop(){
  if(WiFi.status()!=WL_CONNECTED){
    connectWiFi();
  }

  if(Serial.available())
    handleCommand(Serial.readStringUntil('\n'));

  int mic = analogRead(MIC_PIN);

int meter = map(mic,0,4095,0,100);

tft.drawRect(10,300,100,10,ST77XX_WHITE);

tft.fillRect(10,300,meter,10,ST77XX_GREEN);
Wave_update(); Wave_draw(10,220,220,80);



if(Wave_voiceDetected()) 
Orb_setState(ORB_LISTENING);


Orb_update(); Orb_draw(120,95);



Orb_setState(ORB_LISTENING);

Orb_setState(ORB_THINKING);

Orb_setState(ORB_SPEAKING);

Orb_setState(ORB_IDLE);
// Wave_begin(34); // moved to setup()

Chat_update();
// Chat_addMessage(cmd, CHAT_USER);
System_update(); Scheduler_update();
System_setState(STATE_IDLE);
// TTS_speak(answer);
}

