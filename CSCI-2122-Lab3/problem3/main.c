#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>


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
 
        
        if (swapped == false)
            break;
    }
}




int main()
{
    int maxInteger = 0;
    int numberOfIntegers = 0;
    int *bitmap = NULL;
    int *sequence = NULL;
    int currentNumber = 0;
    bool repeat;
    int biggestSequence;
    

    scanf("%d %d",&maxInteger,&numberOfIntegers);
    // this makes our array of (number of slots, each slot of int size bytes)
    bitmap = calloc(numberOfIntegers,sizeof(int));
    


    for(int i =0;  i<numberOfIntegers; i++){
        repeat = false;
        //scan and store
        scanf("%d",&currentNumber);  

        //checks whether the current number is already in the bitmap
        for(int j = 0 ; j<numberOfIntegers ;j++){
            if (bitmap[j] == currentNumber){
                //bitmap is deleted from the 
                repeat =true;
            }
        }

        //if its not in the bitmap then its stored
        if(!repeat){
            bitmap[i] = currentNumber;
        }
    }

    //sorting
    bubbleSort(bitmap,numberOfIntegers);
    

    //we do the same algorithm but without the calloc, just store the sequence length, the biggestOne we keep for next

    int sequenceLength = 0;
    //sequence finding
    for(int i =0; i<numberOfIntegers;i++){
        //checks whether the current number and the next are a sequence
        if(bitmap[i]+1 == bitmap[i+1] && bitmap[i] !=0 && bitmap[i+1] !=0){
            sequenceLength++;
        //a fix for the end of a sequence not being recognized, gives the end of the sequence array slot
        }else if(bitmap[i]-1 == bitmap[i-1] && bitmap[i] !=0 && bitmap[i-1] !=0){
            sequenceLength++;
            biggestSequence = sequenceLength;//current biggestSequence
            sequenceLength = 0; //restart sequence counter
        }
    }

     sequenceLength = 0;
    //sequence finding
    for(int i =0; i<numberOfIntegers;i++){
        //checks whether the current number and the next are a sequence
        if(bitmap[i]+1 == bitmap[i+1] && bitmap[i] !=0 && bitmap[i+1] !=0){
            sequenceLength++;
        //a fix for the end of a sequence not being recognized , gives the end of the sequence array slot
        }else if(bitmap[i]-1 == bitmap[i-1] && bitmap[i] !=0 && bitmap[i-1] !=0){
            sequenceLength++; 
            if(sequenceLength == biggestSequence){//if two sequences are the same length then the first one equal to biggest will print
             sequence = calloc(sequenceLength,sizeof(int));
                int offset = i-sequenceLength+1;//start of 
                
                for(int j= 0; j<sequenceLength+1;j++){
                    sequence[j] = bitmap[offset];//store the sequence in new array
                   
                    offset+=1;//will keep increasing until sequencelength value which is the end of the sequence
                    
                }
                i == numberOfIntegers;//biggest sequence found, end loop
            }
            sequenceLength = 0; //restart sequence counter
            
        }
    }



    printf("Max sequence:");
    for(int i =0; i<biggestSequence;i++){
        printf(" %d",sequence[i]);
    }




    // //printout
    // printf("Max sequence:");
    // for(int i =0; i<numberOfIntegers; i++){
    //     printf(" %d",bitmap[i]);
    // }
   
     return 0;
}
