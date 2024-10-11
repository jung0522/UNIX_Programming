#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if the file name was passed as a command-line argument
    if (argc != 2) {
        printf("Usage: %s <file name>\n", argv[0]);
        return 1;
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    int num;
    int count = 0;
    int sum = 0;

    // Read numbers from the file and calculate sum and count
    while (fscanf(file, "%d", &num) != EOF) {
        sum += num;
        count++;
    }

    // Close the file
    fclose(file);

    // Calculate the average
    if (count > 0) {
        double average = (double)sum / count;
        // Print results
        printf("count = %d ", count);
        printf("sum = %d ", sum);
        printf("ave = %lf ", average);
        printf("\n");
    } else {
        printf("No numbers found in the file.\n");
    }

    return 0;
}

