#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ALPHABET_SIZE 26
#define REQUIRED_LETTERS 7

static int check_word(char *buffer, char *used) {
    assert(buffer != NULL);
    unsigned n = strlen(buffer);
    if (n < 7) {
        return 0;
    }

    memset(used, 0, ALPHABET_SIZE);
    int count = 0;

    for (int i = 0; i < n; i++) {
        char c = buffer[i];
        assert(isalpha(c) && isupper(c));

        int idx = c - 'A';
        if (used[idx] == 0) {
            count++;
            used[idx] = 1;
        }
    }

    return count == REQUIRED_LETTERS;
}

static int count_words(char **words, int n, const char *used) {
    assert(words != NULL);
    assert(used != NULL);
    int count = n;

    for (int i = 0; i < n; i++) {
        char *word = words[i];
        for (int j = 0; word[j]; j++) {
            int c = word[j] - 'A';
            if (!used[c]) {
                count--;
                break;
            }
        }
    }
    return count;
}

int main() {
    int n;
    if (scanf("%d", &n) < 1) {
        printf("Inout error, expecting integer.");
        return 1;
    }

    char buffer[30];
    char *words[n];
    for (int k = 0; k < n; k++) {
        scanf("%29s", buffer);
        words[k] = strdup(buffer);
    }

    char used[ALPHABET_SIZE];

    for (int k = 0; k < n; k++) {
        if (check_word(words[k], used)) {
            printf("%s :", words[k]);

            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (used[i]) {
                    printf(" %c", i + 'A');
                }
            }

            printf(" ; %d\n", count_words(words, n, used));
        }
    }
    return 0;
}
