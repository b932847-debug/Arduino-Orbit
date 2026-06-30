#include "AI.h"
#include "Gemini.h"

static bool busy=false;

void AI_begin(){
    Gemini_begin();
}

String AI_ask(const String &prompt){
    busy=true;
    String reply=Gemini_generate(prompt);
    busy=false;
    return reply;
}

bool AI_isBusy(){
    return busy;
}

void AI_update(){
    Gemini_update();
}
