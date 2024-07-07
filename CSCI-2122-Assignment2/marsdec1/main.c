/*
Created by Javier Wahn
Banner:B00935618
Program function: takes in strings of bits which are decoded to obtain multiple  integers which
will then be printed at the end of each loop of the program
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bitmap_setReverse(char *bitmap,int i);
void bitmap_resetReverse(char *bitmap,int i);
void bitmap_set(char *bitmap,int i);
void bitmap_reset(char *bitmap,int i);
int bitmap_testReverse(char *bitmap,int i);
int finalNumberSet(int bitmap, int i);
int finalNumberReset(int bitmap, int i);
char *bitmap_new(int size);

int main() {
    
    //initial var declratrion
    int loopSize;//number of lines of bytes we will receieve
    scanf("%d",&loopSize);
    int lineLength = 0;//number of bytes we will receieve in current loop
    int counter = 0;//seperate counter for intSize bit placement
    
   
    //For problem 1, the number of bytes will range from 0 to 5
     char *byteLine = bitmap_new(40);//5 slots, 2 bytes each [1111 1111][1111 1111][1111 1111][1111 1111][1111 1111]
     unsigned char *intSize = bitmap_new(5);

     for(int i =0; i<loopSize;i++){//wich line are we on

        scanf("%d",&lineLength); //how many bytes are incoming
    
        //stores all the bytes in current line
        for(int j = 0; j<lineLength; j++){//loops for the amount of bytes
            scanf("%x",&byteLine[j]);//%x for hex
        }

        //after all bytes have been stored
        for(int k=0;k<5;k++){//moves the first 5 bits from byteline[j] into intSize
            int currentBit = bitmap_testReverse(byteLine,k);//get bits 0 to 5 in reverse aka 7 to 2
            
            /*
            since the spacing has to be exact in intSize in terms of position
            we can format it like this so the order is the same in the bits
            for when we dereference *intSize. e.g we assume the bit starts like this[x,x,b0,b1,b2,b3,b4,b5] x are ignored
            */
            
            switch(k){
                case 0:
                    counter = 4;
                    break;
                case 1:
                    counter = 3;
                    break;
                case 2:
                    counter = 2;
                    break;
                case 3:
                    counter =1;
                    break;
                case 4:
                    counter = 0;
                    break;
            }
            /*
            hindsight is 20 20 but i couldve used the solution i used on decodedInt where since i knew the 
             length of the dataType, i just put every bit at the left side and shifted to remove all the useless zeroes
             on the right of the inputted bits,this solution is just ugly as sin in comparison.
            */
            
            if(currentBit == 0){
                bitmap_reset(intSize,counter);//move bit from byteline to intSize
            }else if(currentBit == 1){
                bitmap_set(intSize,counter);//move bit from byteline to intSize
            }
         }

       
         int numberSize = *intSize;//how big is the integer in bits
         int decodedInteger = 0;//we will store here our decoded integer
        

         //we now want to ignore the first 5 bits and store the x bits after x= numberSize

         counter = 31; 
         for(int j = 5; j<numberSize+5;j++){
         int currentBit = bitmap_testReverse(byteLine,j);

         if(currentBit == 0){
            decodedInteger= finalNumberReset(decodedInteger,counter);//shift counter times to left and place bit
         }else if(currentBit == 1){
            decodedInteger=  finalNumberSet(decodedInteger,counter);//shift counter times to left and place bit
         }

            counter--;//keeps in memory where we are in int as we store the bits  from the left to right (bit 31 to 0 as an int has 4 bytes)
            
        }
         decodedInteger = (decodedInteger >>32-numberSize);//shifts to the right as to fix the zeroes left over to the left and get the right int value
    
          // printout
         if(lineLength >0){ //if no byte is inputted in this line we ignore it
            printf("Line %d, integer 1: %d\n",i+1,decodedInteger);
        }
    }
    return 0;
}


//function gets the bit in position i with the assumption that the array bit positions are not reversed as usual i.e [b0,b1,b2,b3,b4,b5,b6,b7]
//we assume this because at the start we scanf all the hex values and those are reversed like in lab3 (as in [b7,b6,b5,b4,b3,b2b,b1])
 int bitmap_testReverse(char *bitmap,int i){
	int slot = i/8;
	i = i%8;
	switch(i){
		case 0:
			i = 7;
			break;
		case 1:
			i  = 6;
			break;
		case 2:
			i  = 5;
			break;
		case 3:
			i  = 4;
			break;
		case 4:
			i  = 3;
			break;
		case 5:
			i  = 2;
			break;
		case 6:
			i  = 1;
			break;
		case 7:
			i = 0;
			break;
	}
	return (bitmap[slot] >> i) & 1; 
}
//function sets bits to 1 in reverse order, i.e if in the source binary number bit0 == 1,  then in bitmap[0] << 7 will be == 1
 void bitmap_setReverse(char *bitmap,int i){
	int slot = i/8;
	i = i%8;
	switch(i){
		case 0:
			i = 7;
			break;
		case 1:
			i  = 6;
			break;
		case 2:
			i  = 5;
			break;
		case 3:
			i  = 4;
			break;
		case 4:
			i  = 3;
			break;
		case 5:
			i  = 2;
			break;
		case 6:
			i  = 1;
			break;
		case 7:
			i = 0;
			break;
	}
	bitmap[slot] =bitmap[slot] | (1<<i);
}
//function sets bits to 1 in reverse order, i.e if in the source binary number bit0 == 0,  then in bitmap[0] << 7 will be == 0
 void bitmap_resetReverse(char *bitmap,int i){
	int slot = i/8;
	i = i%8;
	switch(i){
		case 0:
			i = 7;
			break;
		case 1:
			i  = 6;
			break;
		case 2:
			i  = 5;
			break;
		case 3:
			i  = 4;
			break;
		case 4:
			i  = 3;
			break;
		case 5:
			i  = 2;
			break;
		case 6:
			i  = 1;
			break;
		case 7:
			i = 0;
			break;
	}

	bitmap[slot] = bitmap[slot] & ~(1<<i);
}
//functiond does bit manip with int sizes specifically, sets bits in position i as 1
int finalNumberSet(int bitmap, int i){   
    return bitmap =bitmap | (1<<i);
}
//functiond does bit manip with int sizes specifically, resets bits in position i as 0
int finalNumberReset(int bitmap, int i){
   return bitmap =bitmap & ~(1<<i);
}
//function returns a bitmap with "size" bits
 char *bitmap_new(int size) {
    return calloc(1, (size + 7) >> 3); //mallocates + memset to 0 
}
//function sets bits in position i == to 1
 void bitmap_set(char *bitmap,int i){
	int slot = i/8;
	i = i%8;
	bitmap[slot] =bitmap[slot] | (1<<i);
}
//function sets bits in position i == to 0
 void bitmap_reset(char *bitmap,int i){
	int slot = i/8;
	i = i%8;

	bitmap[slot] = bitmap[slot] & ~(1<<i);
}
