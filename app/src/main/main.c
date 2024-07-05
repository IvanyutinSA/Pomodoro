#include <stdlib.h>
#include <stdio.h>
#include "../lib/list.h"
#include "../lib/env.h"

void user_interface(Env *env);

int main() {
    Env *env;
    env = env_create(NULL);

    while (!env_get(env, "stop", (void *) 1)) {
        user_interface(env);
    }
}

void env_set_predefined_properites(Env *env) {
    env_add(env, "stop", (void *) 0);
    env_add(env, "timer.seconds", (void *) 15);
    env_add(env, "route", "/menu");
}

void user_interface(Env *env) {
    char *route;
    route = env_get(env, "route", "/menu");
    env_get()
}

void stop(Env env) {
    eng_set(env, "stop", (void *) 1);
}
