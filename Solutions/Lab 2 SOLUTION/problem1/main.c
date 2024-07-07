#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    float final = 0;

    for (int i = 0; i < n; i++) {
        int amount;
        char name[10];
        float price;
        scanf("%d %s %f", &amount, name, &price);
        float total = amount * price;
        printf("%s : %.2f\n", name, total);
        final += total;
    }
    printf("Total : %.2f\n", final);
    return 0;
}
