//
// Created by Alex Brodsky on 2023-09-29.
//

#include "arraylst.h"
#include <stdlib.h>
/* Allocates a new string-list
 * parameter:
 *   capacity : posiitve integer denoting the maximum number of items in the list
 * returns:
 *   a pointer to the new list
 */
extern arraylst_t *arraylst_new(int capacity) {
    arraylst_t *list = calloc(1,sizeof(arraylst_t));
    list->items = calloc(capacity,sizeof(int)); // allocate space for the items array EACH POINTER TAKES SIZEOF(INT) IT FUCKING WORKS LMAO WTF
    list->capacity = capacity;
    list->size = 0;
    return list;

}
/* Adds a string to the end of the string-list
 * parameter:
 *   list : pointer to the list
 *   item : pointer to the string to be added
 * returns:
 *   index of the string on success or -1 on failure
 */
extern int arraylst_add(arraylst_t *list, void *item) {
    int returnal = list->size;//end of the arraylist
    list->items[returnal] = item;//in the list struct list.items[x] is changed to store the pointer "*item"     
    if(list->items[returnal] == NULL){
        return -1; //if failed since the list[x] is not storing the pointer "item", instead is NULL
    }
    list->size++;//we just added 1 new item
    return returnal; //since this is the last item to be added, the size should be correct
}
/* Gets the item at specified location in the string-list
 * parameter:
 *   list : pointer to the list
 *   idx : index of item to get.  0 <= idx < size
 * returns:
 *   pointer to item on success or NULL on failure
 */
extern void * arraylst_get(arraylst_t *list, int idx) {
     
     if(list->items[idx] == NULL){
         return NULL;
     }
     
     return list->items[idx];
}
/* Removes the item at specified location in the item-list
 * parameter:
 *   list : pointer to the list
 *   idx : index of item to remove.  0 <= idx < size
 * returns:
 *   1 onf success and 0 on failure
 */
extern int arraylst_remove(arraylst_t *list, int idx) {
    list->items[idx] = NULL;
    list ->items[idx] = list->items[idx+1];
    // if(list->items[idx]){

    // }
    list->size-=1;
    return 1;
}
/* Destroy the list, freeing the items array and the list struct.
 * parameter:
 *   list : pointer to the list
 * returns:
 *   None
 */
extern void arraylst_destroy(arraylst_t *list) {



}
