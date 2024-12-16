#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  

#define FILENAME "data.txt"

int main() {
    pid_t pid;
    FILE *file;

    // Fork a new process
    pid = fork();

    if (pid < 0) {  // Error in fork
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        // Open file in write mode
        file = fopen(FILENAME, "w");
        if (file == NULL) {
            perror("Failed to open file");
            return 1;
        }

        char buffer[256];
       

        // Read from stdin and write to file
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            fprintf(file, "%s", buffer);
        }

        fclose(file);  // Close the file
        exit(0);  // Exit child process
    } else {  // Parent process
        // Wait for the child process to finish
        wait(NULL);  // Wait for the child to terminate

        // Open file in read mode
        file = fopen(FILENAME, "r");
        if (file == NULL) {
            perror("Failed to open file");
            return 1;
        }

        char ch;
      

        // Read from file and print to stdout
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }

        fclose(file);  // Close the file
    }

    return 0;
}

