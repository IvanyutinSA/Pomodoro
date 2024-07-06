#include <stdlib.h>
#include <stdio.h>
#include "../lib/env.h"
#include "../lib/cli/list.h"
#include "../lib/input.h"

void user_interface(Env *env);
void cmd_stop(Env *env);
void cmd_menu(Env *env);
void cmd_navig(Env *env);
void cmd_error(Env *env);
void env_set_predefined_properites(Env *env);

void env_display_vars_keys(Env *env) {
    int row;
    List *list;
    list = env->vars;
    row = 1;
    printf("\033[%d;70H|-------------\n", row++);
    printf("\033[%d;70H|Env variables\n", row++);
    printf("\033[%d;70H|-------------\n", row++);
    while (list != NULL) {
        EnvVar *var = list->entry;
        printf("\033[%d;70H|%s\n", row++, var->key);
        list = list->next;
    }
    printf("\033[%d;70H|-------------\n", row++);
}

int string_cmp(void *x, void *y) {
    return strcmp((char *) x, (char *) y);
}

int main() {
    Env *env;
    env = env_create(NULL);

    env_set_predefined_properites(env);

    char *route;

    while(!env_get(env, "stop", (void *) 1)) {
        printf("\033[2J");
        env_display_vars_keys(env);
        printf("\033[1;1H");
        route = (char *) env_get(env, "route", "/error");
        printf("Current route: %s\n", route);
        // env_display_vars_keys(env);
        ((void (*)(Env *)) env_get(env, route, cmd_stop))(env);
    }
}

void env_set_predefined_properites(Env *env) {
    env_add(env, "vacant", malloc(sizeof(char)*256));
    env_add(env, "stop", 0);
    env_add(env, "route", "/");
    env_add(env, "/", cmd_navig);
    env_add(env, "/menu", cmd_menu);
    env_add(env, "/error", cmd_error);
    env_add(env, "/list/interactive", cmd_list_interactive);
}

void cmd_menu(Env *env) {
    char user_input;
    printf("Menu\n");
    printf("Options:\n");
    printf("1. Interactive list\n");
    printf("\n");
    printf("Option: ");
    scanf("%c", &user_input);
    switch (user_input) {
        case '1':
            env_set(env, "route", "/list/interactive");
            break;
        case '\n':
            printf("It sucks!\n");
            break;
        default:
            printf("\nIncorrect Input. Press any key\n");
            getchar();
            break;
    }
}

void cmd_stop(Env *env) {
    env_set(env, "stop", (void *) 1);
    env_display_vars_keys(env);
    printf("Stopped\n");
}

// Here's a really huge memory leak
void cmd_navig(Env *env) {
    char *route;
    int c;

    route = (char *) malloc(sizeof(char)*256);
    printf("%s\n", (char *) env_get(env, "route", "/"));;
    printf("Route: ");
    read_line(route);
    if (env_contains(env, route)) {
        env_set(env, "route", route);
    } else {
        free(route);
        printf("Program doesn\'t have this route\ntry again.\n");
    }
}

void cmd_error(Env *env) {
    printf("\nError was occured\n");
    cmd_stop(env);
}

