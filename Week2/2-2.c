#include <unistd.h>  // Header file for access() function
#include <stdio.h>   
#include <stdlib.h>  

int main(void)
{

    if (access("linux.txt", F_OK) == -1) {
        // If the file doesn't exist, use perror() to print an error message
        perror("linux.txt");
        
        exit(1);
    }

    // If the file exists, the program exits normally 
    return 0;
}

