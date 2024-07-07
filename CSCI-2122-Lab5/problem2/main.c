#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
    int amountTmp = 1;
    char nameTmp[19];
    float unitCostTmp;
    int listSize= 0 ;
    int removed = 0;

    linked_list_t *shoppingList = ll_new();//our linked list

    struct shoppingItem{
        int amount;
        char name[19];
        float unitCost;
    };

    while(amountTmp!=0){
        scanf("%d %s %f",&amountTmp,&nameTmp,&unitCostTmp);

        struct shoppingItem *item =calloc(1,sizeof(struct shoppingItem));//new struct

        //set the values in the struct
        item->amount = amountTmp;
        strcpy(item->name,nameTmp);
        item->unitCost = unitCostTmp;

        //store
        ll_add_back(shoppingList,item);
    }

    listSize = ll_size(shoppingList);
    //iterator
    ll_node_t *currentNode = shoppingList->head;
    ll_node_t *secondNode = currentNode->next;

    //after everything is stored
    for(int i = 0;i<listSize;i++){
        //find the node we need
        struct shoppingItem *item1 = (struct shoppingItem *)currentNode->item;
        for(int j = i+1; j<listSize-1;j++){//-1 since the last one is always the "end" node
            //we compare item1 to every other item in the list, item2 contains a tmp of each of these items
            struct shoppingItem *item2 = (struct shoppingItem *)secondNode->item;   //SEGMENTATIUN FAULT HERE FIXI!!!!!!!!!!!!
            //if we find two nodes that are of the same item
            if(!strcmp(item1->name,item2->name) && item1->unitCost == item2->unitCost){
                item1->amount += item2->amount;
                ll_remove(shoppingList,secondNode);//remove duplicate 
                //restpre item
                currentNode->item = item1;
                listSize -=1;//we removed a node
                removed = 1;//Bool
            }else{
                removed = 0;//Bool
            }
            //iterate
            if(removed){//checks whether we removed the node before and if we did:
                secondNode = currentNode->next; //the next node is the one after currentNode[currentNode][->next]
            }else{
                secondNode = secondNode->next;//the one after secondNode [currentNode][secondNode][->next]
            }
            
        }
        currentNode = currentNode->next;
        if(currentNode == NULL){
            break;
        }
        secondNode = currentNode->next;//resets secondNode position relative to the new currentNode
    }

    //printout
    currentNode = shoppingList->head;
    for(int i = 0; i<listSize;i++){
        struct shoppingItem *item1 = (struct shoppingItem *)currentNode->item;
        if(item1->amount > 0){
            printf(
            "%d %s %.2f\n",
            item1->amount,item1->name,item1->unitCost
            );
        }
        currentNode = currentNode->next;
        if(currentNode == NULL){
            break;
        }
    }
    
    return 0;
}
