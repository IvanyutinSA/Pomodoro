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
    EnvVar *var;
    var = (EnvVar *) malloc(sizeof(EnvVar));
    var->key = key;
    var->val = val;
    list_insert(env->vars, var);

    return 0;
}

//Silly
int env_delete(Env *env, char *key) {
    return list_delete(env->vars, key, env->cmp);
}

//Silly
void *env_get(Env *env, char *key, void *default_val) {
    void *val;
    EnvVar *var;
    var = (EnvVar *) malloc(sizeof(EnvVar));
    var->key = key;
    val = list_search(env->vars, var, env->cmp);
    if (val == NULL) {
        val = default_val;
    }
    free(var);
    return val;
}

// if was returned -1, then you don't have key dependency
int env_set(Env *env, char *key, void *content) {
    EnvVar *var;
    var = (EnvVar *) list_search(env->vars, key, env->cmp)->entry;
    if (var == NULL) {
        return -1;
    }
    var->val = content;
    return 0; 
}

int env_contains(Env *env, char *key) {
    EnvVar *var;
    int is_contain;
    var = (EnvVar *) malloc(sizeof(EnvVar));
    var->key = key;
    is_contain = !(list_search(env->vars, var, env->cmp) == NULL);
    free(var);
    return is_contain;
}
