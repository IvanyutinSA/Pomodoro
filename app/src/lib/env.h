#ifndef ENV_H
#define ENV_H

# include "list.h"
# include "string.h"

typedef struct Env {
    List *vars;
    void *cmp;
} Env;

typedef struct EnvVar {
    char *key;
    void *val;
} EnvVar;

Env *env_create(List *vars);
Env *env_root();

int env_cmp(void *x, void *y); 
int env_add(Env *env, char *key, void *val); 
int env_delete(Env *env, char *key); 
void *env_get(Env *env, char *key, void *default_val); 
int env_set(Env *env, char *key, void *content);
int env_contain(Env *env, char *key); 

#endif
