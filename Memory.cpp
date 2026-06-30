#include "Memory.h"
static const uint8_t MAX_MEM=20;
static String mem[MAX_MEM];
static uint8_t used=0;
void Memory_begin(){used=0;}
void Memory_add(const String &role,const String &text){
 String line=role+": "+text;
 if(used<MAX_MEM) mem[used++]=line;
 else{
   for(int i=0;i<MAX_MEM-1;i++) mem[i]=mem[i+1];
   mem[MAX_MEM-1]=line;
 }
}
String Memory_recent(uint8_t count){
 String out="";
 if(count>used) count=used;
 for(uint8_t i=used-count;i<used;i++) out+=mem[i]+"\n";
 return out;
}
void Memory_clear(){used=0;}
