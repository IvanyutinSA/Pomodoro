#include "../list.h"
#include <stdlib.h>
#include <string.h>

typedef struct Env {
    List *vars;
    void *cmp;
} Env;

typedef struct EnvVar {
    char *key;
    void *val;
} EnvVar;

int env_cmp(void *x, void *y) {
    EnvVar *u, *v; 
    u = (EnvVar *)x;
    v = (EnvVar *)y;
    return strcmp(u->key, v->key);
} 

// scope -> Env
Env *env_create(Env *parent) {
    Env *env;
    EnvVar *var;
    env = (Env *) malloc(sizeof(Env));
    var = (EnvVar *) malloc(sizeof(Env));
    
    var->key = "Scope";
    var->val = parent;

    env->vars = (List *) malloc(sizeof(List));
    env->vars->entry = var;
    env->vars->next = NULL;
    env->cmp = (void *) env_cmp;
    return env;
}

// Silly
int env_add(Env *env, char *key, void *val) {
    EnvVar var;
    var.key = key;
    var.val = val;
    list_insert(env->vars, &var);

    return 0;
}

//Silly
int env_delete(Env *env, char *key) {
    return list_delete(env->vars, key, env->cmp);
}

//Silly
void *env_get(Env *env, char *key, void *default_val) {
    void *val;
    val = list_search(env->vars, key, env->cmp);
    if (val == NULL) {
        val = default_val;
    }
    return val;
}
