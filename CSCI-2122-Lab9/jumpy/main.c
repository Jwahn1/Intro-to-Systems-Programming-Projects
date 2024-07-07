
#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *search = fopen(argv[1],"rb"); //our file 

    unsigned int offset = 0;

    // Output the initial offset
    printf("%u\n", offset);


    // Read a new value for offset
    fread(&offset, sizeof(int), 1, search);

    

    // While the value is not 0
    while (offset != 0) {
        // rint the last value found in search and that was stored in offset
        printf("%d\n", offset); 

        // move to this new random location based on offset's value
        fseek(search, offset, SEEK_SET);

        // Read a new value for offset
        fread(&offset, sizeof(int), 1, search);
    }

    // Close the file
    fclose(search);

    return 0;
}
