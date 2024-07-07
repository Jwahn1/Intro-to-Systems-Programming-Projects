#include <stdio.h>

long min_bits(long x, long y) {
    long result;
    /* Determine which x or y has fewer bits.
     * Use the popcnt instruction to count the number of bits in a long
     * This instruction calculates the number of bits set to 1 in the source operand and
     * returns the count in the destination operand (must be a register).
     */
    asm ("popcnt %1, %%rax\n\t;"    
        "popcnt %2, %%rdx\n\t"
        "cmpq %%rdx,%%rax\n\t"   //rdx - rax i think?
        "jge yIsBigger\n\t" //if rdx is bigger jump
        "movq %1, %0\n\t" //result = x
        "jmp end\n\t"
        "yIsBigger:\n\t"
        "movq %2, %0\n\t" //result = y
        "end:"
            : "=r" (result)
            : "r" (x), "r" (y)
            : "%rax","%rdx" );

    return result;
}

int call_min_bits(long x, long y) {
    long n;
    /* Call the min_bits function above
     */
    asm (
        "call min_bits"
        :"=r" (n)
        :"r" (x), "r" (y)
    );

    return (int)n;
}

unsigned int sum(unsigned int *data, long size) {
    unsigned int result = 0;
    /* Computes the sum of the integers in data array
     */

     asm (
        "mov $0, %0\n\t"           // Initialize result to 0
        "start:\n\t"
        "add (%2), %0\n\t"  //result = result + data[n]
        "add $4, %2\n\t"          // n +=1
        "dec %1\n\t"              //  size--
        "jnz start\n"              //loop will continue until size == 0
        : "+r" (result)            
        : "r" (size), "r" (data)  
        :                          
    );                     
    return result;
}
 
int main() {
    int n;
    int data[5] = {1, 2, 3, 4, 5};

    scanf("%d", &n);  /* read in the test to perform */ 
    switch(n) {
        case 0:
            printf("%ld = min_bits(%d, %d)\n", min_bits(8,7), 7, 8);
            break;

        case 1:
            printf("%d = call(%d, %d)\n", call_min_bits(15,16),15, 16);
            break;

        case 2:
            printf("%d = sum(data)\n", sum(data, 5));
            break;

        default:
            break;
    }
    return 0;
}


