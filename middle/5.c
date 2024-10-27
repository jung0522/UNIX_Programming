#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>   
#include <stdlib.h>   
#include <errno.h>    

#define SIZE 1024  // Buffer size

int main(void) {
    int fdin, fdout; 
    char buf[SIZE];
    ssize_t bytes_read, bytes_written;

    // Open the source file (dummy) for reading
    fdin = open("f1.dat", O_RDONLY);
    if (fdin < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file (copy) for writing (create if it doesn't exist)
    fdout = open("f2.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fdout < 0) {
        perror("Error opening destination file");
        close(fdin);
        exit(EXIT_FAILURE);
    }

    // Copy the content from dummy to copy
    while ((bytes_read = read(fdin, buf, SIZE)) > 0) {
        bytes_written = write(fdout, buf, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(fdin);
            close(fdout);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read < 0) {
        perror("Error reading from source file");
    }

    // Close the file descriptors
    close(fdin);
    close(fdout);

    return 0;
}


