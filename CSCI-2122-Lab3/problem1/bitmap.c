//
// Created by Alex Brodsky on 2023-09-21.
//
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

extern char *bitmap_new(int size) {
    return calloc(1, (size + 7) >> 3);
}

/* YOUR CODE HERE
 */
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
