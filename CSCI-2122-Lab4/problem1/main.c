#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int listSize;
    int amountTemp;
    char nameTemp[19];
    float unitCostTemp;
    int counter = 0;

    
    struct item{
        int amount;
        char name[19];
        float unitCost;
    };

    scanf("%d",&listSize);
    struct item *shoppingList = calloc(listSize,sizeof(struct item)); //array of item structs
    
    //stores all three vars in each struct 
    for(int i = 0 ; i<listSize;i++){
        scanf("%d %s %f",&amountTemp,&nameTemp,&unitCostTemp);

        shoppingList[i].amount = amountTemp;
        strcpy(shoppingList[i].name,nameTemp);
        shoppingList[i].unitCost = unitCostTemp;
        counter++;//seperate listSize
    }   

    // after all the structs are made
    //hold x struct and iterate again and if x.name = x+n struct.name then x.amount + x+n.amount and delete x+n struct

    for (int i = 0; i < listSize; i++){
        for(int j = i+1; j<listSize ; j++){
            if(!strcmp(shoppingList[i].name,shoppingList[j].name) && shoppingList[i].unitCost == shoppingList[j].unitCost){//match found between two structs
                shoppingList[i].amount += shoppingList[j].amount; //both replicas get merged
                shoppingList[j].amount = 0;//removes struct from list sort of, we check later if its 0
                counter -= 1; //reduces the size of the list
            }
        }
    }
    
    //printout
    printf("%d\n",counter);
    for(int i = 0 ; i<listSize;i++){
        //ignores removed structs
        if(shoppingList[i].amount > 0){
            printf(
            "%d %s %.2f\n",
            shoppingList[i].amount,shoppingList[i].name,shoppingList[i].unitCost
            );
        }
    }   

    
    return 0;
}
