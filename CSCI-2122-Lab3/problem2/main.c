#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "bitmap.h"

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
 
        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}




int main()
{
    int maxInteger = 0;
    int numberOfIntegers = 0;
    int *bitmap = NULL;
    int currentNumber = 0;
    bool repeat;
    int zeroRepeat = 0;

    

    scanf("%d %d",&maxInteger,&numberOfIntegers);
    // this makes our array
    bitmap = calloc(numberOfIntegers,sizeof(int));
    


    for(int i =0;  i<numberOfIntegers; i++){
        repeat = false;
        scanf("%d",&currentNumber);  

        //checks whether the current number is already in the bitmap
        for(int j = 0 ; j<numberOfIntegers ;j++){
            if (bitmap[j] == currentNumber){
                //bitmap is deleted from the 
                bitmap[j] = 0;
                repeat =true;
            }
         }
         

        //if its not in the bitmap then its stored
        if(!repeat){
            bitmap[i] = currentNumber;
        }

        if(currentNumber == 0){
            zeroRepeat++;
        }

    }

    //sorting
    bubbleSort(bitmap,numberOfIntegers);

    //printout
    printf("Odd:");
    if(zeroRepeat % 2 != 0){
        printf(" 0");
    }
    for(int i =0; i<numberOfIntegers; i++){
        if(bitmap[i] > 0){
            printf(" %d",bitmap[i]);
        }
    }
   
    return 0;
}
