#include <stdio.h>
#include "../../list.h"
#include "../../env.h"

void cmd_list_interactive(Env *env) {
    List *list;
    char *vacant = (char *) env_get(env, "vacant", NULL);
    char *route = (char *) env_get(env, "route", NULL);
    scanf(vacant, "%s|list", route);
    printf("Fine\n");
}
