#ifndef TIMER_H
#define TIMER_H

struct Stopwatch {
    double total_secs;
    double last_check;
    int is_paused;
};
struct Stopwatch create_stopwatch();

double get_time(struct Stopwatch stopwatch);
void pause_stopwatch(struct Stopwatch stopwatch);
void unpause_stopwatch(struct Stopwatch stopwatch);

#endif
