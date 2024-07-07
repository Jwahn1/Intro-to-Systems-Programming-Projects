#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 65536

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: jumpy <binary file>\n");
        return 1;
    }

    FILE *fin = fopen(argv[1], "rb");
    if (!fin) {
        printf("Could not open file '%s' for reading\n", argv[1]);
        return 1;
    }

    long offset;
    unsigned int value = 0;
    do {
        offset = value;
        printf("%d\n", value);
        fseek(fin, offset, SEEK_SET);
        if(fread(&value, 1, sizeof(int), fin) != sizeof (int)) {
            printf("Read failed at offset %ld\n", offset);
            break;
        }
    } while (value);

    fclose(fin);
    return 0;
}
