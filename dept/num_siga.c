#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// SIGINT (Ctrl-C) signal handler
void sigint_handler(int sig) {
    // Ignore SIGINT signal and do nothing
    printf("\nSIGINT received, but ignoring Ctrl-C...\n");
}

int main(void) {
    struct sigaction sa;

    // Set the handler for SIGINT signal
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    // Set the sigaction for SIGINT signal
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    short i = 0;
    while(1) {
        if (i < 0)
            i = 0; 
        printf("%d\r", i++);  // Print the number and overwrite the same line
        fflush(stdout);  // Force the output buffer to flush so the print appears immediately
        usleep(100000);  // Add a small delay (0.1 seconds) to prevent excessive flickering on screen
    }

    return 0;
}

