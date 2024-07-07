//
// Created by Alex Brodsky on 2023-09-21.
//
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

//dont get too confused this is suposed to be an array at the end of the day 
//what i should really understand what the [n] size is actually supposed to be, i need to understand this 
//fundemantally
extern char *bitmap_new(int size) {
    return calloc(1, (size + 7) >> 3); //mallocates + memset to 0 
}

//im wondering whether this if statement might not work with the variable size of problem 2 bitmaps
//i%8
//i == 7 7%8 =
//get the bitma[slot] and 8*n==slot via the number in i and remove the if statement here	
//im trying to get 
extern int bitmap_test(char *bitmap,int i){
	int slot = 0;
	if(i > 7 && i<16){
		i = i -8;
		slot = 1;
	}else if(i>15 && i<24){
		i = i -16;
		slot = 2;
	}else if(i > 23){
		i = i -24;
		slot = 3;
	}

	return (bitmap[slot] >> i) & 1; 
}

extern void bitmap_set(char *bitmap,int i){
	int slot = 0;
	if(i > 7 && i<16){
		i = i -8;
		slot = 1;
	}else if(i>15 && i<24){
		i = i -16;
		slot = 2;
	}else if(i > 23){
		i = i -24;
		slot = 3;
	}
	bitmap[slot] =bitmap[slot] | (1<<i);
}

extern void bitmap_reset(char *bitmap,int i){
	int slot = 0;
	if(i > 7 && i<16){
		i = i -8;
		slot = 1;
	}else if(i>15 && i<24){
		i = i -16;
		slot = 2;
	}else if(i > 23){
		i = i -24;
		slot = 3;
	}

	bitmap[0] = bitmap[0] & ~(1<<i);
}

extern  void bitmap_toggle(char *bitmap,int i){
	int slot = 0;
	if(i > 7 && i<16){
		i = i -8;
		slot = 1;
	}else if(i>15 && i<24){
		i = i -16;
		slot = 2;
	}else if(i > 23){
		i = i -24;
		slot = 3;
	}

	bitmap[slot] =bitmap[slot] ^ (1<<i);
}
