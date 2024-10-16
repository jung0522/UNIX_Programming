#include <stdio.h>
#include <time.h>
#include <errno.h>

int main() {
    // Declare a time_t variable to store the current time
    time_t current_time;

    // Get the current time. time() returns (time_t)-1 on failure
    if (time(&current_time) == (time_t)-1) {
        perror("Failed to get current time");
        return 1; 
    }

    // Use the tm structure to convert the time into a human-readable format
    struct tm *local_time = localtime(&current_time);

    // localtime() returns NULL on failure
    if (local_time == NULL) {
        perror("Failed to convert to local time");
        return 1;
    }

    // Declare a string array to store the formatted date 
    char date_string[100];

    // Use strftime to format the time string 
    if (strftime(date_string, sizeof(date_string), "%Y. %m. %d (%a) %H:%M:%S %Z", local_time) == 0) {
        fprintf(stderr, "Failed to format date and time\n");
        return 1;
    }

    // Print the result
    printf("%s\n", date_string);

    return 0;
}

