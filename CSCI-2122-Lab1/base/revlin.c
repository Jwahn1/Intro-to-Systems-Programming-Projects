#include <stdio.h>
#include <string.h>

int main() {
    int n = 0;
    char tmp[80];
    char *lines[100];

    while (fgets(tmp, 80, stdin) != NULL) {
        lines[n] = strdup(tmp);
        n++;
    }

    for (int i = n - 1; i >= 0; i--) {
        printf("%s", lines[i]);
    }
    return 0;
}
