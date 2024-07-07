#include "../../input.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../env.h"
#include <sys/select.h>
#include "../../timer.h"

Timer *__timer_get(Env *env);
int __timer_delete(Env *env);
char *__timer_get_representation(Timer *timer);
int __timer_set_bound(Env *env, char *bound_str);
int __timer_parse_bound(char *bound_str, long *bound);

void cmd_timer_interactive(Env *env) {
    Timer *timer;
    char *timer_representation, *option_str, *value;
    char option, c;
    fd_set rfds;
    int retval;
    struct timeval tv;

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    option_str = malloc(sizeof(char)*24);
    value = malloc(sizeof(char)*24);
    timer = __timer_get(env);
    timer_representation = __timer_get_representation(timer);

    printf(
        "Timer\n"
        "Your timer: %s\n"
        "Options:\n"
        "1. Pause\n"
        "2. Unpause\n"
        "3. Reset\n"
        "4. Set time\n"
        "Option: ",
        timer_representation
    );
    fflush(stdout);
    free(timer_representation);

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
        case '1':
            timer_pause(timer);
            break;
        case '2':
            timer_unpause(timer);
            break;
        case '3':
            __timer_delete(env);
            break;
        case '4':
            printf("Value: ");
            read_line(value);
            if (__timer_set_bound(env, value) == 0) {
                __timer_delete(env);
            }
        default:
            sprintf(option_str, "%c", option);
            ((void (*)(Env *, char *))env_get(env, "/global/option/list/add", NULL))(env, option_str);
            break;
    }
}

Timer *__timer_get(Env *env) {
    Timer *timer;
    char *timer_destination, *timer_bound_destination;
    long bound; 

    timer_destination = (char *) malloc(sizeof(char) * 256);
    timer_bound_destination = (char *) malloc(sizeof(char) * 256);

    sprintf(timer_destination, "%s|timer", (char *) env_get(env, "route", ""));
    sprintf(timer_bound_destination, "%s|timer_bound", (char *) env_get(env, "route", ""));

    if(env_contains(env, timer_destination)) {
        timer = env_get(env, timer_destination, NULL);
        free(timer_destination);
    } else {
        bound = (long) env_get(env, timer_bound_destination, 0);
        timer = timer_init(bound);
        env_add(env, timer_destination, timer);
    }

    free(timer_bound_destination);

    return timer;
}

int __timer_delete(Env *env) {
    char *timer_destination;
    int status_code;

    timer_destination = (char *) malloc(sizeof(char) *256);

    sprintf(timer_destination, "%s|timer", (char *) env_get(env, "route", ""));

    status_code = env_delete(env, timer_destination);
    free(timer_destination);

    return status_code;
}

// if returned -1, then maybe bound_str in wrong format
int __timer_set_bound(Env *env, char *bound_str) {
    char *timer_bound_destination;
    int status_code;
    long bound = 0;

    if (__timer_parse_bound(bound_str, &bound) != 0) {
        printf("dfsd\n");
        getchar();
        return -1;
    }

    status_code = 0;
    timer_bound_destination = (char *) malloc(sizeof(char) *256);

    sprintf(timer_bound_destination, "%s|timer_bound", (char *) env_get(env, "route", ""));

    if (env_contains(env, timer_bound_destination)) {
        status_code = env_set(env, timer_bound_destination, (void *) bound);
        free(timer_bound_destination);
    } else {
        env_add(env, timer_bound_destination, (void *) bound);
    }

    return status_code;
}

int __timer_parse_bound(char *bound_str, long *bound) {
    int stage, j;
    char time[3][24];
    char c;

    stage = 0;

    printf("%s\n", bound_str);
    j = 0;
    for(int i = 0; i < strlen(bound_str); i++) {
        if(bound_str[i] == ':') {
            time[stage][j] = '\0';
            j = 0;
            stage++;
        } else {
            time[stage][j++] = bound_str[i];
        }
    }
    time[2][j] = '\0';

    *bound = atoi(time[0])*3600 + atoi(time[1])*60 + atoi(time[2]);
    printf("%ld", *bound);

    return 0;
}

char *__timer_get_representation(Timer *timer) {
    char *timer_representation;
    long seconds;

    timer_representation = malloc(sizeof(char) *64);
    
    seconds = abs((int) timer_get_time(timer));
    if (timer_is_completed(timer)) {
        sprintf(timer_representation, "-%02ld:%02ld:%02ld", (seconds/3600), (seconds/60)%60, seconds%60);
    } else {
        sprintf(timer_representation, "%02ld:%02ld:%02ld", (seconds/3600), (seconds/60)%60, seconds%60);
    }

    if (timer->paused) {
        strcat(timer_representation, " (paused)");
    }

    return timer_representation;
}
