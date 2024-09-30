#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // For related directory functions

int main() {
    DIR *dp;
    struct dirent *dent; // Pointer to directory entry structure

    dp = opendir("."); // Open the current directory

    // Read the files in the directory one by one
    while ((dent = readdir(dp))) {
        // Print the name of the file or directory
        printf("Name : %s ", dent->d_name);
        // Print the inode number of the file
        printf("Inode : %d\n", (int)dent->d_ino);
    }
    
    // Close the directory
    closedir(dp);
} 



