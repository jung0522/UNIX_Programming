#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    // Open 'test.txt' file
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    // Get the file size
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Failed to get file size");
        close(fd);
        return 1;
    }
    size_t filesize = st.st_size;

    // Map the file into memory
    char *mapped = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("Failed to map file to memory");
        close(fd);
        return 1;
    }

    // Print the mapped content
    printf("File contents:\n%s\n", mapped);

    // Unmap the memory
    if (munmap(mapped, filesize) == -1) {
        perror("Failed to unmap memory");
    }

    // Close the file
    close(fd);
    return 0;
}

