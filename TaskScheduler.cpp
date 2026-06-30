#include <Arduino.h>
#include "TaskScheduler.h"
struct Task{TaskFn fn;unsigned long iv,last;};
static Task tasks[8];
static int count=0;
void Scheduler_begin(){count=0;}
void Scheduler_add(TaskFn fn,unsigned long iv){
 if(count<8){tasks[count++]={fn,iv,0};}
}
void Scheduler_update(){
 unsigned long now=millis();
 for(int i=0;i<count;i++){
   if(now-tasks[i].last>=tasks[i].iv){
      tasks[i].last=now;
      if(tasks[i].fn) tasks[i].fn();
   }
 }
}
