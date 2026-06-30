#include "BootScreen.h"
#include "Display.h"

void BootScreen_begin(){
  BootScreen_draw("Initializing...",0);
}

void BootScreen_draw(const char *status,int percent){
  auto &tft=Display_getTFT();
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setCursor(40,40);
  tft.println("ORBIT OS");
  tft.setTextSize(1);
  tft.setCursor(40,80);
  tft.println(status);
  tft.drawRect(20,280,200,14,ST77XX_WHITE);
  int w=map(percent,0,100,0,198);
  tft.fillRect(21,281,w,12,ST77XX_CYAN);
}
