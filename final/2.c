#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int count = 0;  // Variable to count the number of SIGINT signals received

// Signal handler for SIGINT
void sigint_handler(int sig) {
    count++;  // Increment the counter every time SIGINT is received
    printf("\nHandler is called %d time(s)\n", count);  // Print the counter value
}

int main(void) {
    struct sigaction sa;

    // Set up the sigaction structure
    sa.sa_handler = sigint_handler;  // Specify the handler for SIGINT
    sa.sa_flags = 0;  // No flags
    sigemptyset(&sa.sa_mask);  // Initialize an empty signal set

    // Register the handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction failed");
        exit(1);
    }

    // Infinite loop with 5-second sleep
    while (1) {
        printf("I'm in infinite loop\n");
        sleep(5);  // Sleep for 5 seconds
    }

    return 0;
}

