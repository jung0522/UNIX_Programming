#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd1, fd2;
    int n;
    char buf[BUFSIZ];  

    // Check if correct number of arguments are passed
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <copy_file>\n", argv[0]);
        exit(1);
    }

    // Open the source file in read-only mode
    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("Error opening source file");
        exit(1);
    }

    // Open or create copy file 
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 == -1) {
        perror("Error opening/creating destination file");
        close(fd1);
        exit(1);
    }

    // Read from the source file and write to the copy file
    while ((n = read(fd1, buf, BUFSIZ)) > 0) {
        if (write(fd2, buf, n) != n) {
            perror("Error writing to copy file");
            close(fd1);
            close(fd2);
            exit(1);
        }
    }

    // Error handling for read
    if (n == -1) {
        perror("Error reading from source file");
        close(fd1);
        close(fd2);
        exit(1);
    }

    // Close the files
    if (close(fd1) == -1) {
        perror("Error closing source file");
        exit(1);
    }
    if (close(fd2) == -1) {
        perror("Error closing destination file");
        exit(1);
    }

    return 0;
}

