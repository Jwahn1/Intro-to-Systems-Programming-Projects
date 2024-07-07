//
// Created by Alex Brodsky on 2023-09-20.
//

#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

typedef struct ll_node {
    struct ll_node *prev;
    struct ll_node *next;
    void *item;
} ll_node_t;

typedef struct linked_list {
    ll_node_t *head;
    ll_node_t *tail;
} linked_list;

extern linked_list_t ll_new() {
    linked_list_t * list = calloc(1,sizeof(linked_list_t));
    return list;
}

extern void ll_destroy(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list != NULL);

    while (list->head != NULL) {
        ll_node_t *tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }

    free(list);
}

static ll_node_t *new_node(void *item, ll_node_t *prev, ll_node_t *next) {
    ll_node_t *n = calloc(1, sizeof(ll_node_t));
    if (n != NULL) {
        n->item = item;
        n->prev = prev;
        n->next = next;
    }
    return n;
}


extern int ll_add_front(linked_list_t ll, void *item) {
    linked_list  *list = (linked_list *)ll;
    assert(list);

    ll_node_t *n = new_node(item,NULL, list->head);
    if (n != NULL) {
        if (list->tail == NULL) {
            list->tail = n;
        } else {
            list->head->prev = n;
        }
        list->head = n;
    }
    return n != NULL;
}

extern int ll_add_back(linked_list_t ll, void *item) {
    linked_list  *list = (linked_list *)ll;
    assert(list);

    ll_node_t *n = new_node(item,list->tail, NULL);
    if (n != NULL) {
        if (list->head == NULL) {
            list->head = n;
        } else {
            list->tail->next = n;
        }
        list->tail = n;
    }
    return n != NULL;
}

extern void * ll_remove_front(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        ll_node_t *n = list->head;
        list->head = list->head->next;
        if (list->head == NULL) {
            list->tail = NULL;
        } else {
            list->head->prev = NULL;
        }

        item = n->item;
        free(n);
    }
    return item;
}

extern void * ll_remove_back(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list);
    
    void *item = NULL;
    if (list->tail != NULL) {
        ll_node_t *n = list->tail;
        list->tail = list->tail->prev;
        if (list->tail == NULL) {
            list->head = NULL;
        } else {
            list->tail->next = NULL;
        }

        item = n->item;
        free(n);
    }
    return item;
}

extern void * ll_get_front(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->head->item;
    }
    return item;
}

extern void * ll_get_back(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->tail->item;
    }
    return item;
}

extern int ll_size(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list);
    int count = 0;
    for (ll_node_t *ptr = list->head; ptr != NULL; ptr = ptr->next) {
        count++;
    }
    return count;
}

extern int ll_is_empty(linked_list_t ll) {
    linked_list  *list = (linked_list *)ll;
    assert(list);
    return list->head == NULL;
}

/************************************************************************
 * Your code below 
 ************************************************************************/

typedef struct iterator {
    linked_list *list;
    ll_node_t *cur;
    int next;
} iterator;

extern ll_iterator_t  ll_iterator_new(linked_list_t list) {
    assert(list);
    iterator *iter = calloc(1, sizeof(iterator));
    assert(iter);
    iter->list = (linked_list *)list;
    return iter;
}

extern void ll_iterator_destroy(ll_iterator_t iter) {
    assert(iter);
    free(iter);
}

extern void *ll_next(ll_iterator_t iter) {
    iterator *it = (iterator *)iter;
    assert(iter);

    if (ll_has_next(iter)) {
        if (it->cur) {
            it->cur = it->cur->next;
        } else {
            it->cur = it->list->head;
        }
        it->next = 1;
        return it->cur->item;
    }
    it->next = 0;
    return NULL;
}

extern int ll_has_next(ll_iterator_t iter) {
    iterator *it = (iterator *) iter;
    assert(iter);

    if (it->cur) {
        return it->cur->next != NULL;
    } else {
        return it->list->head != NULL;
    }
}

extern int ll_has_prev(ll_iterator_t iter) {
    iterator *it = (iterator *) iter;
    assert(iter);

    if (it->cur) {
        return it->cur->prev != NULL;
    } else {
        return it->list->head != NULL;
    }
}

extern void *ll_prev(ll_iterator_t iter) {
    iterator *it = (iterator *)iter;
    assert(iter);

    if (ll_has_prev(iter)) {
        if (it->cur) {
            it->cur = it->cur->prev;
        } else {
            it->cur = it->list->tail;
        }
        it->next = -1;
        return it->cur->item;
    }
    it->next = 0;
    return NULL;
}

extern int ll_add(ll_iterator_t iter, void *item) {
    iterator *it = (iterator *) iter;
    assert(iter);
    assert(item);

    int rc = 0;
    it->next = 0;
    if (it->cur == NULL) {
        rc = ll_add_front(it->list, item);
        it->cur = it->list->head;
    } else if (it->cur->next == NULL) {
        rc = ll_add_back(it->list, item);
        it->cur = it->list->tail;
    } else {
        ll_node_t *n = new_node(item, it->cur, it->cur->next);
        rc = n != NULL;
        if (rc) {
            n->prev->next = n;
            n->next->prev = n;
            it->cur = n;
        }
    }
    return rc;
}

extern void *ll_set(ll_iterator_t iter, void *item) {
    iterator *it = (iterator *) iter;
    void *old = NULL;

    assert(iter);
    assert(item);

    if (it->next) {
        old = it->cur->item;
        it->cur->item = item;
    }
    return old;
}

extern void *ll_remove(ll_iterator_t iter){
    iterator *it = (iterator *) iter;
    assert(iter);

    if (it->next) {
        ll_node_t *node = it->cur;
        if (ll_next > 0) {
            it->cur = it->cur->prev;
        } else {
            it->cur = it->cur->next;
        }
        it->next = 0;
        if (node->prev == NULL) {
            assert(it->list->head == node);
            return ll_remove_front(it->list);
        } else if(it->cur->next == NULL) {
            assert(it->list->tail == node);
            return ll_remove_back(it->list);
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            void *item = node->item;
            free(node);
            return item;
        }
    }
    return NULL;
}
