#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    // Using 5-5 constant by sysconf() in an array
    long values[] = {
        _SC_ARG_MAX,          // Maximum number of arguments to a command
        _SC_CHILD_MAX,        // Maximum number of child processes
        _SC_NGROUPS_MAX,      // Maximum number of groups
        _SC_OPEN_MAX,         // Maximum number of open files
        _SC_JOB_CONTROL,      // Job control availability
        _SC_SAVED_IDS,        // Support for saved user IDs
        _SC_VERSION,          // System version
        _SC_STREAM_MAX        // Maximum number of streams
    };

    // Names corresponding to each constant
    const char *names[] = {
        "ARG_MAX",
        "CHILD_MAX",
        "NGROUPS_MAX",
        "OPEN_MAX",
        "JOB_CONTROL",
        "SAVED_IDS",
        "VERSION",
        "STREAM_MAX"
    };

    // Number of constants
    int num_values = sizeof(values) / sizeof(values[0]);

    // Fetch and print the value of each constant
    for (int i = 0; i < num_values; i++) {
        long value = sysconf(values[i]);

        // Error handling
        if (value == -1) {
            perror("sysconf error");
        } else {
            // Print the name and value of the constant
            printf("%s: %ld\n", names[i], value);
        }
    }

    return 0;
}
