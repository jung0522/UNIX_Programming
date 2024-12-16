#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

// Function to convert a word to lowercase
void to_lowercase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

// Define a structure for a word and its frequency
typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} Word;

// Comparator function for sorting words by frequency (descending order)
int compare(const void *a, const void *b) {
    return ((Word*)b)->count - ((Word*)a)->count;  // Sort by count in descending order
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Could not open file.\n");
        return 1;
    }

    Word words[1000];
    int word_count = 0;
    char word[MAX_WORD_LENGTH];

    // Read words from the file and count their occurrences
    while (fscanf(file, "%s", word) != EOF) {
        to_lowercase(word);  // Convert word to lowercase

        // Check if the word is already in the list
        int found = 0;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i].word, word) == 0) {
                words[i].count++;
                found = 1;
                break;
            }
        }

        // If the word is new, add it to the list
        if (!found) {
            strcpy(words[word_count].word, word);
            words[word_count].count = 1;
            word_count++;
        }
    }

    fclose(file);

    // Sort words by frequency in descending order
    qsort(words, word_count, sizeof(Word), compare);

    // Print the words and their frequencies
    for (int i = 0; i < word_count; i++) {
        printf("%s: %d\n", words[i].word, words[i].count);
    }

    return 0;
}

