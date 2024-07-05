#include <time.h>

struct Stopwatch {
    time_t total_secs;
    time_t last_pause;
    int is_paused;
};

struct Stopwatch create_stopwatch() {
    struct Stopwatch stopwatch;
    stopwatch.total_secs = 0;
    stopwatch.last_pause = time(NULL);
    stopwatch.is_paused = 0;

    return stopwatch;
}

double get_time(struct Stopwatch stopwatch) {
    return stopwatch.total_secs - (stopwatch.is_paused - 1) * (time(NULL) - stopwatch.last_pause);
}

void pause_stopwatch(struct Stopwatch stopwatch) {
    stopwatch.total_secs += time(NULL) - stopwatch.last_pause;
    stopwatch.is_paused = 1;
}

void unpause_stopwatch(struct Stopwatch stopwatch) {
    stopwatch.last_pause = time(NULL);
    stopwatch.is_paused = 0;
}

