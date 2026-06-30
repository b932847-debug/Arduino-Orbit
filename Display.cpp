
#include "Display.h"
#include "DisplayConfig.h"
#include "OrbRenderer.h"
#include "WaveRenderer.h"
#include "ChatRenderer.h"

static Adafruit_ST7789 tft(TFT_CS,TFT_DC,TFT_RST);
static DisplayPage currentPage=PAGE_HOME;
static uint16_t backgroundColor=ST77XX_BLACK;
static uint16_t textColor=ST77XX_WHITE;
static bool initialized=false;
static uint32_t lastFrame=0;
static const uint16_t FRAME_TIME=16;

Adafruit_ST7789 &Display_getTFT(){ return tft; }

void Display_begin(){
    tft.init(TFT_WIDTH,TFT_HEIGHT);
    tft.setRotation(0);
    tft.fillScreen(backgroundColor);
    tft.setTextWrap(true);
    tft.setTextColor(textColor);
    initialized=true;
}

void Display_setPage(DisplayPage page){ currentPage=page; }
DisplayPage Display_getPage(){ return currentPage; }

void Display_clear(){ tft.fillScreen(backgroundColor); }
void Display_setBackground(uint16_t color){ backgroundColor=color; }
void Display_setTextColor(uint16_t color){ textColor=color; tft.setTextColor(color); }

static void drawStatusBar(){
    tft.fillRect(0,0,TFT_WIDTH,20,ST77XX_BLACK);
    tft.drawFastHLine(0,20,TFT_WIDTH,ST77XX_DARKGREY);
    tft.setCursor(6,6);
    tft.setTextColor(ST77XX_WHITE);
    tft.print("Orbit OS Beta 2");
}

void Display_update(){
    if(!initialized) return;
    if(millis()-lastFrame<FRAME_TIME) return;
    lastFrame=millis();

    tft.fillScreen(backgroundColor);
    drawStatusBar();

    switch(currentPage){
        case PAGE_BOOT:
            break;
        default:
            Orb_update();
            Orb_draw(120,82);
            Chat_update();
            Wave_draw(10,265,220,45);
            break;
    }
}
