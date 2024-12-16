#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd[2]; // Array to hold the file descriptors for the pipe
    pid_t pid;
    char buffer[BUFFER_SIZE];
    
    // Create an unnamed pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a new process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        // Child process
        close(pipefd[0]); // Close unused read end of the pipe
        
        printf("Type your string: ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        // Remove newline character from the input
        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Write the string to the pipe
        if (write(pipefd[1], buffer, strlen(buffer)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]); // Close the write end of the pipe
    } else {
        // Parent process
        close(pipefd[1]); // Close unused write end of the pipe
        
        // Read the string from the pipe
        ssize_t bytesRead = read(pipefd[0], buffer, BUFFER_SIZE);
        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0'; // Null-terminate the string
        printf("%s has %zu char.\n", buffer, strlen(buffer));

        close(pipefd[0]); // Close the read end of the pipe
    }

    return 0;
}

