#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char **argv) {
    unsigned long timeout;
    if (argc < 3) {
        printf("Usage: ./timeout <time> <executable> [arguments]\n");
        return 1;
    } else if (sscanf(argv[1], "%lu", &timeout) != 1 || timeout < 1) {
        printf("Usage: ./timeout <time> <executable> [arguments]\n");
        printf("Illegal time: %s\n", argv[1]);
        return 1;
    }

    int pid = fork();
    if (pid < 0) {
        printf("Error: fork failed\n");
        return 1;
    } else if (pid) {
        sleep(timeout);
        kill(pid, SIGKILL);
    } else {
        execv(argv[2], &argv[2]);
        perror("Oops:");
        return 1;
    }
    return 0;
}
