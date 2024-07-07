#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../list.h"
#include "../../env.h"
#include "../../input.h"

List *__list_get(Env *env);
List *__list_init(Env *env);
char *__list_get_representation(List *list);
int __list_delete(Env *env);
int __list_cmp_string(void *, void *);

void cmd_list_interactive(Env *env) {
    List *list;
    char *list_representation, *value, *option_str;
    char option, c;

    list = __list_get(env);
    option_str = malloc(sizeof(char));
    list_representation = __list_get_representation(list);

    printf(
        "Here is list interactive\n"
        "Your list: %s\n"
        "Options:\n"
        "1. Insert value\n"
        "2. Delete value\n"
        "3. Search value\n"
        "4. Clear list\n"
        "Option: ",
        list_representation
    );
    free(list_representation);

    option = getchar();
    while ((c = getchar()) != '\n') { }

    value = malloc(sizeof(char) * 64);
    
    switch (option) {
        case '1':
            printf("Value: ");
            read_line(value);
            if (list == NULL) {
                list = __list_init(env);
                list->entry = value;
                list->next = NULL;
            } else {
                list_insert(list, value);
            }
            break;
        case '2':
            printf("Value: ");
            read_line(value);
            list_delete(list, value, __list_cmp_string);
            break;
        case '3':
            printf("Value: ");
            read_line(value);
            if (list_search(list, value, __list_cmp_string)) {
                printf("List is containing the value\n");
            } else {
                printf("List is not containing the value\n");
            };
            getchar();
            break;
        case '4':
            __list_delete(env);
            break;
        default:
            sprintf(option_str, "%c", option);
            ((void (*)(Env *, char *))env_get(env, "/global/option/list/add", NULL))(env, option_str);
            break;
    }
}

List *__list_get(Env *env) {
    List *list;
    char *list_destination;

    list_destination = (char *) malloc(sizeof(char *) * 256);

    sprintf(list_destination, "%s|list", (char *) env_get(env, "route", ""));

    list = env_get(env, list_destination, NULL);

    free(list_destination);
    return list;
}

List *__list_init(Env *env) {
    List *list;
    char *list_destination;

    list = malloc(sizeof(List));
    list_destination = (char *) malloc(sizeof(char) * 256);

    sprintf(list_destination, "%s|list", (char *) env_get(env, "route", ""));

    if (env_contains(env, list_destination)) {
        env_set(env, list_destination, list);
        free(list_destination);
    } else {
        env_add(env, list_destination, list);
    }

    return list;
}

int __list_delete(Env *env) {
    char *list_destination;
    int status_code;

    list_destination = (char *) malloc(sizeof(char *) * 256);

    sprintf(list_destination, "%s|list", (char *) env_get(env, "route", ""));

    status_code = env_delete(env, list_destination); 
    free(list_destination);
    return status_code;
}

char *__list_get_representation(List *list) {
    char *value, *list_representation, *block;

    list_representation = malloc(sizeof(char) * 1024);
    strcpy(list_representation, "");

    while (list != NULL) {
        block = malloc(sizeof(char) * 64);
        sprintf(block, "|%s|-->", (char *) list->entry);
        list = list->next;
        strcat(list_representation, block);
        free(block);
    }

    strcat(list_representation, "NULL");
    return list_representation;
};

int __list_cmp_string(void *x, void *y) {
    return strcmp((char *) x, (char *) y);
}
