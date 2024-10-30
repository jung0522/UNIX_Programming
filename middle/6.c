#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time;             // Variable to store the current time
    struct tm *local_time;           // Structure to hold the local time components
    char formatted_time[100];        // Buffer to store the formatted time
    const char *days_in_korean[] = { "일", "월", "화", "수", "목", "금", "토" };  // Korean day names

    // Get the current system time
    current_time = time(NULL);

    // Convert the current time to local time
    local_time = localtime(&current_time);

    // Format the date and time (without weekday initially)
    strftime(formatted_time, sizeof(formatted_time), "%Y. %m. %d.", local_time);

    // Print the formatted date and time with the Korean weekday and time
    printf("%s (%s) %02d:%02d:%02d KST\n", 
           formatted_time, 
           days_in_korean[local_time->tm_wday], 
           local_time->tm_hour, 
           local_time->tm_min, 
           local_time->tm_sec);

    return 0;
}

