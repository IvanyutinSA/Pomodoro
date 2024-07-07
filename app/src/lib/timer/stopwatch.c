#include <stdlib.h>
#include <time.h>

typedef struct Stopwatch {
    time_t total_secs;
    time_t last_pause;
    int paused;
} Stopwatch;

Stopwatch *stopwatch_create() {
    Stopwatch *stopwatch;
    stopwatch = malloc(sizeof(Stopwatch));
    stopwatch->paused = 1;
    stopwatch->total_secs = 0;

    return stopwatch;
}

long stopwatch_get_time(Stopwatch *stopwatch) {
    return stopwatch->total_secs - (stopwatch->paused - 1) * (time(NULL) - stopwatch->last_pause);
}

void stopwatch_pause(Stopwatch *stopwatch) {
    stopwatch->total_secs += time(NULL) - stopwatch->last_pause;
    stopwatch->paused = 1;
}

void stopwatch_unpause(Stopwatch *stopwatch) {
    stopwatch->last_pause = time(NULL);
    stopwatch->paused = 0;
}

