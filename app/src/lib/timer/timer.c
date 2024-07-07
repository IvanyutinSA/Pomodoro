#include <stdlib.h>
#include "../timer.h"

#ifndef TIMER_H

#define TIMER_H
typedef struct Timer {
    time_t bound;
    Stopwatch *stopwatch;
    int paused;
} Timer;

#endif

Timer *timer_init(time_t bound) {
    Timer *timer;
    timer = malloc(sizeof(Timer));
    timer->bound = bound;
    timer->stopwatch = stopwatch_create();

    return timer;
}

long timer_get_time(Timer *timer) {
    return timer->bound - stopwatch_get_time(timer->stopwatch);
}

int timer_is_completed(Timer *timer) {
    return timer_get_time(timer) <= 0;
}

void timer_pause(Timer *timer) {
    stopwatch_pause(timer->stopwatch);
}

void timer_unpause(Timer *timer) {
    stopwatch_unpause(timer->stopwatch);
}

