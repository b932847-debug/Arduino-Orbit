
#include "ChatRenderer.h"
#include "Display.h"

#include <Arduino.h>

struct Message
{
    String text;
    ChatSender sender;
};

static const uint8_t MAX_MESSAGES = 6;
static Message history[MAX_MESSAGES];
static uint8_t messageCount = 0;

static bool thinking = false;
static uint8_t dots = 0;
static unsigned long lastTick = 0;

static void drawBubble(int x,int y,int w,int h,uint16_t color)
{
    auto &tft = Display_getTFT();
    tft.fillRoundRect(x,y,w,h,10,ST77XX_BLACK);
    tft.drawRoundRect(x,y,w,h,10,color);
}

static void wrapText(const String &text,int x,int y)
{
    auto &tft = Display_getTFT();
    tft.setCursor(x,y);

    int col=0;

    for(char c : text)
    {
        if(c=='\n')
        {
            tft.println();
            col=0;
            continue;
        }

        if(col>=26 && c==' ')
        {
            tft.println();
            col=0;
            continue;
        }

        tft.print(c);
        col++;
    }
}

void Chat_begin()
{
    messageCount=0;
    thinking=false;
    dots=0;
}

void Chat_clear()
{
    auto &tft=Display_getTFT();
    tft.fillRect(0,140,240,180,ST77XX_BLACK);
}

void Chat_addMessage(const String &text, ChatSender sender)
{
    thinking=false;

    if(messageCount<MAX_MESSAGES)
    {
        history[messageCount++]={text,sender};
    }
    else
    {
        for(int i=0;i<MAX_MESSAGES-1;i++)
            history[i]=history[i+1];

        history[MAX_MESSAGES-1]={text,sender};
    }
}

void Chat_showThinking()
{
    thinking=true;
}

void Chat_update()
{
    auto &tft=Display_getTFT();

    Chat_clear();

    int y=146;

    for(int i=0;i<messageCount;i++)
    {
        uint16_t color =
            history[i].sender==CHAT_ORBIT ?
            ST77XX_CYAN :
            ST77XX_WHITE;

        drawBubble(8,y,224,32,color);

        tft.setTextColor(color);
        wrapText(history[i].text,18,y+10);

        y+=36;
    }

    if(thinking)
    {
        if(millis()-lastTick>300)
        {
            lastTick=millis();
            dots=(dots+1)%4;
        }

        drawBubble(8,y,224,32,ST77XX_CYAN);

        tft.setCursor(18,y+10);
        tft.setTextColor(ST77XX_CYAN);
        tft.print("Orbit is thinking");

        for(int i=0;i<dots;i++)
            tft.print(".");
    }
}
