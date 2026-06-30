#include "Battery.h"
static uint8_t pin=35;
static float volts=0.0f;
void Battery_begin(uint8_t analogPin){pin=analogPin;}
void Battery_update(){
 int raw=analogRead(pin);
 volts=(raw/4095.0f)*2.0f*3.3f;
}
float Battery_voltage(){return volts;}
int Battery_percent(){
 int p=(int)((volts-3.2f)/(4.2f-3.2f)*100.0f);
 if(p<0)p=0; if(p>100)p=100;
 return p;
}
bool Battery_isCharging(){return false;}
