#pragma once
#include <Arduino.h>

enum ChatSender{
  CHAT_USER,
  CHAT_ORBIT
};

void Chat_begin();
void Chat_clear();
void Chat_addMessage(const String &text, ChatSender sender);
void Chat_showThinking();
void Chat_update();
