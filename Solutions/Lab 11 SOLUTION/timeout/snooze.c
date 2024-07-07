#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    unsigned long time;
    if (argc < 2) {
        printf("Usage: ./snooze <time>\n");
        return 1;
    } else if (sscanf(argv[1], "%lu", &time) != 1 || time < 1) {
        printf("Usage: ./snooze <time>\n");
        printf("Illegal time: %s\n", argv[1]);
        return 1;
    }

    printf("Good night, World!\n");
    fflush(stdout);
    sleep(time);
    printf("Good morning, World!\n");
    return 0;
}
