#include <stdio.h>

int main(int argc, char **argv) {
    // Open the source file for reading
    FILE *source_file = fopen(argv[1], "rb");//r is of reading binary
    FILE *target_file = fopen(argv[2], "wb");//w is for writing binary

    char buffer[4096]; //we will use this to move the contents from one file to the other
     size_t bytes_read;
   // Copy the contents of the source file to the target file
     while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, target_file);
    }


    // Close all files
    fclose(source_file);
    fclose(target_file);


    return 0;
}
