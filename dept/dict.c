#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to compare strings for alphabetical order
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Function to compare strings for reverse alphabetical order
int compare_reverse(const void *a, const void *b) {
    return strcmp(*(const char **)b, *(const char **)a);
}

int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc < 2) {
        printf("Usage: %s <strings...>\n", argv[0]);
        return 1;
    }

    // Print in queue order (original input order)
    printf("Queue Order:\n");
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n\n");

    // Print in stack order (reverse input order)
    printf("Stack Order:\n");
    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n\n");

    // Sort the arguments in alphabetical order
    char *sorted[argc - 1];
    for (int i = 1; i < argc; i++) {
        sorted[i - 1] = argv[i];
    }
    qsort(sorted, argc - 1, sizeof(char *), compare);

    // Print in alphabetical order
    printf("Alphabetical Order:\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%s ", sorted[i]);
    }
    printf("\n\n");

    // Sort the arguments in reverse alphabetical order
    qsort(sorted, argc - 1, sizeof(char *), compare_reverse);

    // Print in reverse alphabetical order
    printf("Reverse Alphabetical Order:\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%s ", sorted[i]);
    }
    printf("\n\n");

    return 0;
}

