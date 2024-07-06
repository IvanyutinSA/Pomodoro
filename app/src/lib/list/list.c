#include <stdlib.h>
#include <stdio.h>

typedef struct List {
    void *entry;
    struct List *next;
} List;

// returns -1 if x < y
//          0 if x = y
//          1 if x > y

void *list_search(List *list, void *target, int cmp(void *, void *)) {
    if (list == NULL) {
        return NULL;
    }
    if (cmp(target, list->entry) == 0) {
        return list->entry;
    }
    return list_search(list->next, target, cmp);
}

// if retured -1, then list may be NULL
int list_insert(List *list, void *target) {
    List *temp_list, *new_node;

    if (list == NULL) {
        return -1;
    }

    new_node = (List *) malloc(sizeof(List));
    new_node->entry = target;
    new_node->next = NULL;

    temp_list = list;
    while (temp_list->next != NULL) {
        temp_list = temp_list->next;
    }
    temp_list->next = new_node;

    return 0;
}

// return -1 if target not in list
// or if its you try to delete first element
int list_delete(List *list, void *target, int cmp(void *, void *)) {
    List *prev, *deleted;
    prev = list;

    if (prev == NULL) {
        return -1;
    } 

    while (prev->next != NULL && cmp(target, prev->next->entry)) {
        prev = prev->next;
    }

    if (prev->next == NULL) {
        return -1;
    } 

    deleted = prev->next;
    prev->next = prev->next->next; 
    free(deleted);

    return 0;
}

int list_size(List *list) {
    int size;
    size = 0;

    while(list != NULL) {
        size++;
        list = list->next;
    }

    return size;
}

int list_destruct(List *list) {
    List *tmp;
    while (list != NULL) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
    return 0;
}
