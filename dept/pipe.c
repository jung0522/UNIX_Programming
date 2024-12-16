#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pd[2]; // File descriptors for the pipe
    pid_t pid;

    // Create a pipe
    if (pipe(pd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Create a child process
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child process
        // Close the read end of the pipe and use the write end
        close(pd[0]);
        dup2(pd[1], STDOUT_FILENO); // Redirect standard output to the write end of the pipe

        // Execute the "ls -l" command
        execlp("ls", "ls", "-l", (char *) NULL);
        perror("execlp");
        exit(1);
    } else { // Parent process
        // Close the write end of the pipe and use the read end
        close(pd[1]);
        dup2(pd[0], STDIN_FILENO); // Redirect standard input to the read end of the pipe

        // Execute the "grep c" command
        execlp("grep", "grep", "c", (char *) NULL);
        perror("execlp");
        exit(1);
    }

    return 0;
}

