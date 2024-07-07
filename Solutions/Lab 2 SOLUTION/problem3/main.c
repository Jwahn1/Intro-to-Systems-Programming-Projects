#include <stdio.h>
#include <string.h>

void static count(const char *word, int *hist) {
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (idx >= 0 & idx < 26) {
            hist[idx]++;
        }
    }
}

void static printline(const int *histogram, int i) {
    if (histogram[i] > 0){
        printf("%c : ", i + 'a');
        for (int j = 0; j < histogram[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
}


int main() {
    int histogram[26];
    char word[30];

    memset(histogram, 0, sizeof(int) * 26);

    for (;;) {
        scanf("%s", word);
        if (!strcmp(".", word)) {
            break;
        }
        count(word, histogram);
    }

    for (int i = 0; i < 26; i++) {
        printline(histogram, i);
    }
    return 0;
}