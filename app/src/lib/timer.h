#ifndef TIMER_H
#define TIMER_H
#include <time.h>

typedef struct Stopwatch {
    time_t total_secs;
    time_t last_check;
    int paused;
} Stopwatch;

Stopwatch *stopwatch_create(); 

long stopwatch_get_time(Stopwatch *stopwatch); 
void stopwatch_pause(Stopwatch *stopwatch); 
void stopwatch_unpause(Stopwatch *stopwatch); 

typedef struct Timer {
    time_t bound;
    Stopwatch *stopwatch;
    int paused;
} Timer;

Timer *timer_init(time_t bound); 
long timer_get_time(Timer *timer); 
int timer_is_completed(Timer *timer); 
void timer_pause(Timer *timer); 
void timer_unpause(Timer *timer); 

#endif
