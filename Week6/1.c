#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(void)
{
    int fd;
    char str[] = "write test";
    
    // Open the file 'test.txt' if it doesn't exist, open in read-write mode
    fd = open("test.txt", O_RDWR | O_CREAT, 0644);
    
    // Error handling for open() function
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    // Write to the file (use strlen() instead of sizeof()) 
    // Because strlen() return actual length or string
    if (write(fd, str, strlen(str)) == -1) {
        perror("Error writing to file");
        close(fd);
        exit(1);
    }

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(1);
    }

    
    return 0;
}

