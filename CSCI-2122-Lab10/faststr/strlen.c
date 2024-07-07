#include <string.h>
#include "strlen.h"

long strlen_byte(const char *str) {
    char *ptr = str;
    while (*ptr) {
        ptr++;
    }
    return ptr - str;
}

long strlen_word(const char *str) {
    char *ptr = str;
    while(1) {
        unsigned long word = *(unsigned long *)ptr;
        for (int i = 0; i < sizeof(unsigned long); i++) {
            if (!(word & 0xff)) {
                return ptr - str;
            }
            word >>= 8;
            ptr++;
        }
    }
}

long strlen_std(const char *str) {
    return strlen(str);
}
