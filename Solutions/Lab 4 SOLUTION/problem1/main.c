#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct item {
    int amount;
    char name[20];
    float price;
};
int main() {
    int n;
    scanf("%d", &n);

    struct item *bill = calloc(n, sizeof(struct item));
    assert(bill);

    for (int i = 0; i < n; i++) {
        scanf("%d %s %f", &bill[i].amount, bill[i].name, &bill[i].price);
    }

    int count = n;
    for (int i = 0; i < n; i++) {
        if (bill[i].amount > 0) {
            for(int j = i + 1; j < n; j++) {
                if (bill[j].amount > 0 && !strcmp(bill[i].name, bill[j].name) &&
                    bill[i].price == bill[j].price) {
                    bill[i].amount += bill[j].amount;
                    bill[j].amount = 0;
                    count--;
                }
            }
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < n; i++) {
        if (bill[i].amount > 0) {
            printf("%d %s %.2f\n", bill[i].amount, bill[i].name, bill[i].price);
        }
    }
    return 0;
}