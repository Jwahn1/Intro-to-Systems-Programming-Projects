#include "ticks.h"

long ticks() {
    static long last;
    long cur;
    long diff;

    asm ("rdtsc;"
         "shlq $32, %%rdx ;"
         "or %%rdx, %%rax;"
         "movq %%rax, %0;"
            : "+r" (cur)
            :
            : "rax", "rdx" );

    diff = cur - last;
    last = cur;
    return diff;
}

