//
// Created by Alex Brodsky on 2023-09-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

/**********************************
 * See bottom of file for your work
 *********************************/

extern linked_list_t * ll_new() {
    linked_list_t * list = calloc(1,sizeof(linked_list_t));
    return list;
}

extern void ll_destroy(linked_list_t *list) {
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


extern int ll_add_front(linked_list_t *list, void *item) {
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

extern int ll_add_back(linked_list_t *list, void *item) {
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

extern void * ll_remove_front(linked_list_t *list) {
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

extern void * ll_remove_back(linked_list_t *list) {
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

extern void * ll_get_front(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->head->item;
    }
    return item;
}

extern void * ll_get_back(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->tail->item;
    }
    return item;
}


/************************************************************************
 * Your code below 
 ************************************************************************/

//go through head to the tail and count each time you go to a new node
extern int ll_size(linked_list_t *list) {
   ll_node_t *currentNode = NULL;
   currentNode = list->head;
    int size = 0;
   while(currentNode != NULL){
       size++;
       currentNode = currentNode->next; //currentNode takes the value of the node after itself
   }
   
   return size;//i think my problem gets stuck on this while loop, maybe .next is never equal to NULL for some reason
}

extern int ll_is_empty(linked_list_t *list) {
    
    if(list->head == NULL){//specific case
       return 1;
   }
   return 0;
}

extern int ll_insert(linked_list_t *list, ll_node_t *node, void *item) {
  
   if(node == NULL){
       return 0; //failure
   }
    //three nodes we're going to use [node][newNode][rightMostNode]
    ll_node_t *newNode = new_node(item,NULL,NULL);
    ll_node_t *rightMostNode = node->next;
    //give the new node its values
    newNode->item = item;
    //the node after "node" is placed after newNode
    newNode->next= node->next; 
    //the node after "node" is now instead newNode
    node->next = newNode;
    //the node before newNode is now "node"
    newNode->prev = node;
    
    if(newNode->next != NULL){// in case its at the end of the list
        //if we're not at the end of the list then the node before rightMostNode is newNode  
       rightMostNode->prev = newNode;
        return 1;//success
    }

    return 1;//success     
}

extern void * ll_remove(linked_list_t *list, ll_node_t *node) {
    if(node == NULL){
       return NULL; //failure
   }
   
   if(node == list->head){
       list->head = node->next;
   }
   if(node == list->tail){
       list->tail = node->prev;
   }
    //[node->prev][node][node->next]
    //we get node out of the way and stich the ones next to it to each other
    if(node->next != NULL){// in case its at the end of the list
        node->next->prev = node->prev;
    }

    if(node->prev != NULL){// in case its at the start of the list
        node->prev->next = node->next;
    }
    void *item = node->item;
    free(node);
    return item;
   
}
