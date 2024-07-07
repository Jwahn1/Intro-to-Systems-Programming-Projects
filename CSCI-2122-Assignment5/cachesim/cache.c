//
// Created by Alex Brodsky on 2023-11-13.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "main.h"


typedef struct{
    //a bytes index == bytes[index] 
    int *bytes; //a line stores x amount of bytes
    int timestamp;
    int tag; //esentially the lines ID number
} *line_t;


typedef struct{
    line_t *lines;//a set is made up of lines
} *set_t;


typedef struct {
    set_t *sets;//a cache is made up of sets
    unsigned int word_size;
    unsigned int set_amount;
    unsigned int line_amount;
    unsigned int byte_amount;
} caches; //different naming convention to differentiate from the obfuscated cache_t

extern cache_t cache_new(unsigned int word_size, unsigned int sets, unsigned int lines, unsigned int line_size) {
    //allocate memory for the cache
    caches *cache = malloc(sizeof(caches));

    //initializing data structure
    cache->word_size = word_size;
    cache->line_amount = lines;
    cache->set_amount = sets;
    cache->byte_amount = line_size;

    
    //we allocate all the sets stored in the unique cache
    //we have "sets" amount of sets in the cache
    cache->sets = malloc(sets * sizeof(set_t));
    

    //we allocate all lines stored in each set
    for ( int i = 0; i < sets; ++i) {
        //we have to allocate each seperate set first
        cache->sets[i] = malloc(sizeof(set_t));
        //we have "lines" amount of lines in each set
        cache->sets[i]->lines = malloc(lines * sizeof(line_t)); 
    }
    //we allocate all the bytes stored in each line +
     for ( int i = 0; i < sets; ++i) {
        for(int j =0; j<lines;j++){
            //we have to allocate each seperate line first
            cache->sets[i]->lines[j] = malloc(sizeof(line_t)); 
            // in each line we have "line_size" amount of byte
            cache->sets[i]->lines[j]->bytes = malloc(line_size); 
        }
    }

    return (cache_t*)cache; //so return an obfuscated version of  caches *cache?
}


extern void cache_load_word(cache_t handle, unsigned long address, void *word) {
    //parse the private version to a readable version  
    caches *new_handle = (caches *) handle; 


    // 1. Break up the address into a tag, index, and offset.

    //tag(how many bits) = word_size - line_size(remember to transform bytes to bits)
    // 

    //we know address is an unsigned long
    //meaning its 32 bits
    //with bit manipulation we have to set it so its dependent on if its 32 bits or 64 bits 

    unsigned long mask = 1;
    //[0][0]...[1] and then we bit manip
    unsigned int tagLimit = new_handle->word_size - new_handle->line_amount;
    unsigned int tag;
    unsigned  int index;
    unsigned int offset;

    //cache->set[index]->line[tag]-> not sure yet how to store the bytes specifically but = word


    // 2. Use the index to locate the correct set.

    // 3. Use the tag to determine if block of memory that includes the address is in one of the
    // lines in the set.
    
    // 4. If it is (a cache hit), the offset is used to locate the word in that line, the word should be
    // copied into the buffer pointed to by word, and then the function can return.

    // 5. Otherwise, it is a cache miss. In this case, a victim line is selected using the least recently
    // used criteria (LRU) criteria. The line is initialized with the current tag and loaded by calling
    // the function    
}

extern void cache_load_block(cache_t handle, unsigned long address, void *block, unsigned int size) {

}

extern void cache_store_word(cache_t handle, unsigned long address, void *word) {
    
}


