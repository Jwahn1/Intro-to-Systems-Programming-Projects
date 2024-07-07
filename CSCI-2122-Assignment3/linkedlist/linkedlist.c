//
// Created by Alex Brodsky on 2023-09-20.
//

#include <stdio.h>
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
    linked_list_t * list = calloc(1,sizeof(linked_list));
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
typedef struct ll_iterator {
    ll_node_t *current;
    ll_node_t *next;
} ll_iterator;

extern ll_iterator_t  ll_iterator_new(linked_list_t list) {
    ll_iterator * iterator = calloc(1,sizeof(ll_iterator));
    linked_list * listNew = list; // decode list 
    if(listNew->head == NULL){ //special case when calling new - iterator commands one after the other 
        return iterator = list; // this fixes the new - iterator chain of command bug but also introduces a seg fault in append in test 8 ???????????????????
    }
    iterator->next = listNew->head; //iterator placed before list->head
    iterator->current = NULL;

    return iterator;//return the _t since its encapsulated?
}

extern void ll_iterator_destroy(ll_iterator_t iter) {
     free(iter);
}

extern void *ll_next(ll_iterator_t iter) {
    //updating iterator position
   ll_iterator *iterator =  iter; //decode iter
   iterator->current = iterator->next; // what if currently we added
   iterator->next = iterator->current->next;

   iter = iterator; //update iter with new position

   return iterator->current->item; //return item that was in the next position
}

extern int ll_has_next(ll_iterator_t iter) {
    ll_iterator *iterator =  iter;
    ll_node_t *nextNode = iterator->next;
    if(nextNode != NULL){
        return 1;//return if there is a next node
    }
    
    return 0; //return if there isnt a next node
}

//[currentNode] <-> [newNode] <-> [nextNode]  new insertion like this
extern int ll_add(ll_iterator_t iter, void *item) {
    ll_iterator *iterator = iter; //decode iter

    if (iterator->current == NULL){
        return 0; //failure
    }

    //prepare our three nodes
    ll_node_t *newNode = new_node(NULL,NULL,NULL);
    ll_node_t *rightMostNode = iterator->next;
    
    //give the new node its values
    newNode->item = item;
    //the node after "current" is placed after newNode
    newNode->next= iterator->current->next; 
    //the node after "current" is now instead newNode
    iterator->current->next = newNode;
    //the node before newNode is now "current"
    newNode->prev = iterator->current;

     if(newNode->next != NULL){// in case its at the end of the list
        //if we're not at the end of the list then the node before rightMostNode is newNode  
       rightMostNode->prev = newNode;
        return 1;//success
    }

    return 1;
}   
//if i am to understand, before function we have [currentNode], iterator, [nextNode] and the result should be : [newNode], iterator,[nextNode]
//correct! just replace the item value in currentNode with new item
extern void *ll_set(ll_iterator_t iter, void *item) {
    ll_iterator *iterator = iter; //decode iter

    if (iterator->current == NULL){ //fail check
        return NULL; //failure
    }
    void * prevItem = iterator->current->item;//store item before deleting it
    iterator->current->item = item;//update current to have the new item
    return prevItem;

}
//[current],iterator,[nextNode] : result : [beforeCurrent],iterator,[NextNode]
extern void *ll_remove(ll_iterator_t iter){
    ll_iterator *iterator = iter; //decode iter

    if (iterator->current == NULL){ //fail check
        return NULL; //failure
    }

    //now we glue beforeCurrento to nextNode
   ll_node_t *beforeCurrent = iterator->current->prev;
   ll_node_t *nextNode =iterator->next;

   beforeCurrent->next = nextNode;

   if(beforeCurrent->next != NULL){// in case its at the end of the list
        //if we're not at the end of the list then the node before rightMostNode is newNode  
       nextNode->prev = beforeCurrent;
    }

    void *deletedItem = iterator->current->item;//store item before deletion
    iterator->current = iterator->current->prev;//cut currentNode out of the linkedList chain

    return deletedItem;
}
