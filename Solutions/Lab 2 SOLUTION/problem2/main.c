#include <stdio.h>
#include <string.h>

int main() {
    char prev[80] = "";
    char curr[80] = "";

    for (;;) {
        scanf("%s", curr);
        if (!strcmp(".", curr)) {
            break;
        } else if (strcmp(prev, curr)) {
            printf("%s\n", curr);
        }
        strcpy(prev, curr);
    }
    return 0;
}
