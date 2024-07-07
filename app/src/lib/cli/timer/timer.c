#include <bits/types/struct_timeval.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include "../../env.h"
#include "../../timer.h"

char *__stopwatch_get_representation(Stopwatch *stopwatch);
Stopwatch *__stopwatch_get(Env *env);
int __stopwatch_delete(Env *env);
void *__input_get(void *data);

void cmd_stopwatch(Env *env) {
    Stopwatch *stopwatch;
    char *stopwatch_representation, *option_str;
    char option, c;
    fd_set rfds;
    int retval;
    struct timeval tv;

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    option_str = malloc(sizeof(char)*24);
    stopwatch = __stopwatch_get(env);
    stopwatch_representation = __stopwatch_get_representation(stopwatch);

    printf(
        "Stopwatch\n"
        "Your stopwatch: %s\n"
        "Options:\n"
        "1. Pause\n"
        "2. Unpause\n"
        "3. Reset\n",
        stopwatch_representation
    );
    free(stopwatch_representation);

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    retval = select(1, &rfds, NULL, NULL, &tv);

    if (retval) {
        option = getchar();
        while ((c = getchar()) != '\n');
    } else {
        option = 0;
    } 

    switch(option) {
        case '0':
            printf("FINE\n");
            getchar();
            break;
        case '1':
            stopwatch_pause(stopwatch);
            break;
        case '2':
            stopwatch_unpause(stopwatch);
            break;
        case '3':
            __stopwatch_delete(env);
            break;
        default:
            sprintf(option_str, "%c", option);
            ((void (*)(Env *, char *))env_get(env, "/global/option/list/add", NULL))(env, option_str);
            break;
    }
}

char *__stopwatch_get_representation(Stopwatch *stopwatch) {
    char *stopwatch_representation;
    long seconds;
    int hours, minutes;

    stopwatch_representation = malloc(sizeof(char) *64);
    
    seconds = stopwatch_get_time(stopwatch);

    sprintf(stopwatch_representation, "%ld", seconds);
    if (stopwatch->paused) {
        strcat(stopwatch_representation, "(paused)");
    }

    return stopwatch_representation;
}


Stopwatch *__stopwatch_get(Env *env) {
    Stopwatch *stopwatch;
    char *stopwatch_destination;

    stopwatch_destination = (char *) malloc(sizeof(char *) * 256);

    sprintf(stopwatch_destination, "%s|stopwatch", (char *) env_get(env, "route", ""));

    if (env_contains(env, stopwatch_destination)) {
        stopwatch = env_get(env, stopwatch_destination, NULL);
        free(stopwatch_destination);
    } else {
        stopwatch = stopwatch_create();
        env_add(env, stopwatch_destination, stopwatch);
    }

    return stopwatch;
}

int __stopwatch_delete(Env *env) {
    char *stopwatch_destination;
    int status_code;

    stopwatch_destination = (char *) malloc(sizeof(char *) * 256);

    sprintf(stopwatch_destination, "%s|stopwatch", (char *) env_get(env, "route", ""));

    status_code = env_delete(env, stopwatch_destination);
    free(stopwatch_destination);

    return status_code;
}
