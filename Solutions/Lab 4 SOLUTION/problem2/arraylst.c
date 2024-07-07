//
// Created by Alex Brodsky on 2023-09-29.
//

#include <stdlib.h>
#include <assert.h>
#include "arraylst.h"

extern arraylst_t *arraylst_new(int capacity) {
    arraylst_t *list = calloc(1, sizeof (arraylst_t));
    if (list) {
        list->capacity = capacity;
        list->items = calloc(capacity, sizeof(char *));
        assert(list->items);
    }

    return list;
}

extern int arraylst_add(arraylst_t *list, void *item) {
    if (list && list->size < list->capacity) {
         list->items[list->size] = item;
         list->size++;
         return list->size - 1;
    }
    return -1;
}

extern void * arraylst_get(arraylst_t *list, int idx) {
    char *result = NULL;

    if (list && idx >= 0 && idx < list->size) {
        result = list->items[idx];
    }
    return result;
}

extern int arraylst_remove(arraylst_t *list, int idx) {
    char *result = arraylst_get(list, idx);

    if (result) {
        for (; idx + 1 < list->size; idx++) {
            list->items[idx] = list->items[idx + 1];
        }
        list->items[idx] = NULL;
        list->size--;
    }
    return result != NULL;
}

extern void arraylst_destroy(arraylst_t *list) {
    if (list) {
        free(list->items);
        free(list);
    }
}
