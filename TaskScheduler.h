#pragma once
typedef void (*TaskFn)();
void Scheduler_begin();
void Scheduler_add(TaskFn fn,unsigned long intervalMs);
void Scheduler_update();
