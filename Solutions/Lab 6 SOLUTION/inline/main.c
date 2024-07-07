#include <stdio.h>

long one_bits(long x) {
    long n;
    /* Use the popcnt instruction to count the number of bits in a long
     * This instruction calculates the number of bits set to 1 in the source operand and
     * returns the count in the destination operand (must be a register).
     */
    asm ("nop;"      /* replace this with your own assembly code */
            :
            :
            :  );

    asm ("popcnt %1, %0;"
            : "+r" (n)
            : "m" (x)
            :  );

    return n;
}

int only_one_bit(long x) {
    long n;
    /* Return 1 if and only if x has one bit set to 1.
     * Use the popcnt instruction to count the number of bits in a long
     * Use the setz instruction to set the destination to the value of the zero flag
     * Hint: the setz instruction takes an 8-bit register as the destination, e.g., %al
     */
    asm ("nop;"      /* replace this with your own assembly code */
            :
            :
            :  );

    asm ("popcnt %1, %%rax;"
         "cmp $1, %%rax;"
         "setz %%al;"
         "movq %%rax, %0"
            : "+r" (n)
            : "m" (x)
            :  "rax");

    return (int)n;
}

int line(int x, int m, int b) {
    int y;
    /* Computes the formula y = m * x + b
     */
    asm ("nop;"      /* replace this with your own assembly code */
            :
            :
            :  );

    asm ("mov %1, %0;"
         "imul %2, %0;"
         "add %3, %0;"
            : "+r" (y)
            : "m" (x), "m" (m), "m" (b)
            :  );

    return y;
}

int main() {
    int n;
    scanf("%d", &n);  /* read in the test to perform */
    switch(n) {
        case 0:
            printf("%ld = one_bits(%d)\n", one_bits(13), 13);
            break;
        case 1:
            printf("%d = only_one_bit(%d)\n", only_one_bit(13), 13);
            printf("%d = only_one_bit(%d)\n", only_one_bit(8), 8);
            break;
        case 2:
            printf("%d = %d * %d + %d\n", line(3, 4, 5), 3, 4, 5);
            printf("%d = %d * %d + %d\n", line(6, 7, 8), 6, 7, 8);
            break;
        default:
            break;
    }
    return 0;
}


