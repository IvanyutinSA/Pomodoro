#ifndef LIST_H_
#define LIST_H_

typedef struct List {
    void *entry;
    struct List *next;
} List;

List *list_search(List *list, void *target, int cmp(void *, void *)); 
void list_insert(List *list, void *target); 
int list_delete(List *list, void *target, int cmp(void *, void *)); 
int list_size(List *list);

#endif
