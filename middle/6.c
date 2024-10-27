#include <stdio.h>
#include <time.h>  
int main() {
    time_t current_time;  // Variable to store the current time
    struct tm *local_time;  // Structure to hold the local time components
    char formatted_time[100];  // Buffer to store the formatted time

    // Get the current system time 
    current_time = time(NULL);
    
    // Convert the current time to local time 
    local_time = localtime(&current_time);

    // Format the date and time in the desired format
    strftime(formatted_time, sizeof(formatted_time), "%Y. %m. %d. (%a) %H:%M:%S KST", local_time);

    // Print the formatted date and time
    printf("%s\n", formatted_time);

    return 0;
}

