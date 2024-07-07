#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 65536

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: mycp <source file> <target file>\n");
        return 1;
    }

    FILE *fin = fopen(argv[1], "rb");
    if (!fin) {
        printf("Could not open file '%s' for reading\n", argv[1]);
        return 1;
    }

    FILE *fout = fopen(argv[2], "wb");
    if (!fout) {
        printf("Could not open file '%s' for writing\n", argv[2]);
        return 1;
    }

    char *buffer = malloc(BUFSIZE);
    if (!buffer) {
        printf("Could not allocate buffer\n");
        return 1;
    }

    unsigned long len;
    do {
        len = fread(buffer, 1, BUFSIZE, fin);
        if (len > 0) {
            unsigned long wlen = fwrite(buffer, 1, len, fout);
            if (wlen != len) {
                printf("fwrite failed. Tried %lu bytes, got %lu bytes\n", len, wlen);
                return 1;
            }
        }
    } while (len == BUFSIZE);

    fclose(fin);
    fclose(fout);
    free(buffer);
    return 0;
}
