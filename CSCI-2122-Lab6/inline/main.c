#include <stdio.h>

long one_bits(long x) {
    long n;

    /* Use the popcnt instruction to count the number of bits in a long
     * This instruction calculates the number of bits set to 1 in the source operand and
     * returns the count in the destination operand (must be a register).
     */
    
    asm ("popcnt %1, %%rax\n\t"
        "movq %%rax, %0"   
            : "=r" (n)
            : "r" (x)
            : "%rax");

    return n;
}

int only_one_bit(long x) {
    long n = 0;

    /* Return 1 if and only if x has one bit set to 1.
     * Use the popcnt instruction to count the number of bits in a long
     * Use the setz instruction to set the destination to the value of the zero flag
     * Hint: the setz instruction takes an 8-bit register as the destination, e.g., %al
     */
    asm ("popcnt %1, %%rax\n\t"  //how many bits does x have int rax
         "subq $1, %%rax\n\t" // rax - 1
         "cmpq  $0,%%rax\n\t" // if rax == 0 no jmp
         "jne notZero\n\t" //if rax != 0 jmp
         "movq $1 , %0\n\t" //n =1
         "jmp end\n\t" //skips notZero
         "notZero:\n\t"//else rax =0
         "movq $0, %0\n\t" // n = 0
         "end:" 
            : "=r" (n)
            : "r" (x)
            : "%rax" );

    return (int)n;
}

int line(int x, int m, int b) {
    int y;
    /* Computes the formula y = m * x + b
     */
    asm ("movl %1, %%eax\n\t" // rax = x
        "movl %2, %%edx\n\t" // rdx = m
        "imull %%edx, %%eax\n\t" // rax = rax * rdx
        "addl %3, %%eax\n\t" // rax = rax + b
        "movl %%eax, %0" //y = %rax
            : "=r" (y)
            : "r" (x),"r" (m),"r" (b)
            : "%eax","%edx" );

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


