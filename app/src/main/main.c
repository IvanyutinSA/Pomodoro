#include <stdlib.h>
#include <stdio.h>
#include "../lib/env.h"
#include "../lib/cli/list.h"

void user_interface(Env *env);
void stop(Env *env);
void cmd_menu(Env *env);
void env_set_predefined_properites(Env *env);

// int main() {
//     Env *env;
//     env = env_create(NULL);
//     env_set_predefined_properites(env);
//
//     while (!env_get(env, "stop", (void *) 1)) {
//         char *route;
//         route = env_get(env, "route", "/menu");
//         ((void (*)(Env *)) env_get(env, route, stop))(env);
//     }
// }

void display_keys(Env *env) {
    List *list;
    list = env->vars;
    printf("Table\n");
    printf("Key\t|Val\n");
    while (list != NULL) {
        EnvVar *var = list->entry;
        printf("%s\t|%s\n", var->key, (char *) var->val);
        list = list->next;
    }
}

int main() {
    Env *env;
    env = env_create(NULL);
    env_add(env, "1", "Hello");
    env_add(env, "2", "World");
    display_keys(env);
}

void env_set_predefined_properites(Env *env) {
    env_add(env, "vacant", malloc(sizeof(char)*256));
    env_add(env, "stop", (void *) 0);
    env_add(env, "timer.seconds", (void *) 15);
    env_add(env, "route", "/menu");
    env_add(env, "/menu", cmd_menu);
    env_add(env, "/list/interactiave", cmd_list_interactive);
}

void cmd_menu(Env *env) {
    char user_input;
    printf("Menu\n");
    printf("Options:\n");
    printf("1. Interactive list\n");
    printf("\n\n\n");
    printf("Enter what you want... ");
    scanf("%c", &user_input);
    switch (user_input) {
        case 1:
            env_set(env, "route", "/list/interactive");
            break;
        default:
            printf("\nIncorrect Input. Press any key\n");
            getchar();
            break;
    }
}

void stop(Env *env) {
    env_set(env, "stop", (void *) 1);
}
