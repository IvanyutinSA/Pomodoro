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

#endif
