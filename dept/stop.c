#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

// Global variables for remaining time in seconds and milliseconds
volatile int remaining_time;
volatile int remaining_ms;
volatile int timer_running = 1; // Timer running state (1: running, 0: paused)
timer_t timerid; // Timer ID for manual cancellation

// Signal handler for SIGALRM
void timer_handler(int signum) {
    if (remaining_time > 0 || remaining_ms > 0) {
        // Decrement milliseconds or seconds as necessary
        if (remaining_ms == 0) {
            remaining_time--;
            remaining_ms = 99; // Reset milliseconds to 99
        } else {
            remaining_ms--; // Decrease milliseconds by 1
        }

        // Print the remaining time in "seconds.milliseconds" format
        printf("\r  %d . %0d sec  ", remaining_time, remaining_ms);
        fflush(stdout);

        // Set the next alarm for 10 milliseconds if timer is running
        if (timer_running) {
            ualarm(10000, 0);
        }
    } else {
        // Timer finished, print the current time
        struct timeval end_time;
        gettimeofday(&end_time, NULL); // Get the current time
        time_t current_time = (time_t)end_time.tv_sec; // Convert to time_t
        printf("\nTime is up at %s", ctime(&current_time)); // Print the time
        exit(0); // Exit the program
    }
}

// Signal handler for SIGINT (Ctrl + C)
void sigint_handler(int signum) {
    if (timer_running) {
        // Pause the timer
        timer_running = 0;
        printf("\nTimer paused. Press Ctrl + C to resume.\n");

        // Stop the alarm when paused
        ualarm(0, 0); // Disable the alarm
    } else {
        // Resume the timer
        timer_running = 1;
        printf("\nTimer resumed.\n");

        // Trigger the first alarm after 10 milliseconds
        ualarm(10000, 0);
    }
}

int main(int argc, char *argv[]) {
    // Validate command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <duration_in_seconds>\n", argv[0]);
        return 1;
    }

    // Convert the input duration to an integer
    int timer_duration = atoi(argv[1]);
    if (timer_duration <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    // Initialize the timer duration
    remaining_time = timer_duration;
    remaining_ms = 0;

    // Set up the signal handlers
    signal(SIGALRM, timer_handler);  // For the timer
    signal(SIGINT, sigint_handler);  // For Ctrl + C (pause/resume)

    // Trigger the first alarm after 10 milliseconds
    ualarm(10000, 0);

    // Wait indefinitely for signals
    while (1) {
        pause(); // Wait for the next signal
    }

    return 0;
}

