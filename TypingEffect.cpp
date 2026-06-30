#include "TypingEffect.h"
#include "ChatRenderer.h"
void Typing_print(const String &text,unsigned long){
  String build;
  for(char c:text){
    build+=c;
    Chat_addMessage(build,CHAT_ORBIT);
  }
}
