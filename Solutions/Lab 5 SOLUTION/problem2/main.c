#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "linked_list.h"

struct item {
    int amount;
    char name[20];
    float price;
};

int main() {
    linked_list_t *list = ll_new();


    for (;;) {
        struct item line;
        scanf("%d %s %f", &line.amount, line.name, &line.price);
        if (line.amount == 0) {
            break;
        }

        struct item *entry = calloc(1, sizeof(struct item));
        assert(entry);
        *entry = line;
        ll_add_back(list, entry);
    }

    for (ll_node_t *node = list->head; node; node = node->next) {
        struct item *entry = (struct item *)node->item;
        if (entry->amount > 0) {
            for (ll_node_t *node2 = node->next; node2; node2 = node2->next) {
                struct item *entry2 = (struct item *)node2->item;
                if (entry2->amount > 0 && !strcmp(entry->name, entry2->name) &&
                        entry->price == entry2->price) {
                    entry->amount += entry2->amount;
                    entry2->amount = 0;
                }
            }
        }
    }

    for (ll_node_t *node = list->head; node; node = node->next) {
        struct item *entry = (struct item *)node->item;
        if (entry->amount > 0) {
            printf("%d %s %.2f\n", entry->amount, entry->name, entry->price);
        }
    }
    return 0;
}