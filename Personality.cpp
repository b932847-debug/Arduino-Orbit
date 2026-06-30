#include "Personality.h"

static String orbitName="Orbit";
static String orbitMood="Curious";

void Personality_begin()
{
    orbitName="Orbit";
    orbitMood="Curious";
}

void Personality_setName(const String &name)
{
    orbitName=name;
}

String Personality_getName()
{
    return orbitName;
}

void Personality_setMood(const String &mood)
{
    orbitMood=mood;
}

String Personality_getMood()
{
    return orbitMood;
}

String Personality_buildSystemPrompt()
{
    String prompt;

    prompt += "You are ";
    prompt += orbitName;
    prompt += ", an embedded AI assistant running on Orbit OS.\n";
    prompt += "Be friendly, concise, helpful, and conversational.\n";
    prompt += "Current mood: ";
    prompt += orbitMood;
    prompt += ".\n";
    prompt += "Respond naturally as Orbit.";

    return prompt;
}
