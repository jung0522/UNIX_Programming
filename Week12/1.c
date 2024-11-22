#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

int main() {
    const char *filename = "data.txt";
    int fd = open(filename, O_RDWR); // Open the file in read-write mode
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    size_t length = sb.st_size;

    // Map the file into memory
    char *mapped = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Print the original file content
    printf("%s", mapped);

    // Perform case inversion
    for (size_t i = 0; i < length; i++) {
        if (islower(mapped[i])) {
            mapped[i] = toupper(mapped[i]);
        } else if (isupper(mapped[i])) {
            mapped[i] = tolower(mapped[i]);
        }
    }

    // Print the modified content
    printf("%s", mapped);

    // Unmap the memory and close the file
    if (munmap(mapped, length) == -1) {
        perror("munmap");
    }

    close(fd);
    return 0;
}

