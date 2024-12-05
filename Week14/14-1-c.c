#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7000           // Port number of the server
#define BUFFER_SIZE 1024    // Buffer size for data transfer

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    int client_fd;
    struct sockaddr_in server_addr;
    int nums[BUFFER_SIZE / sizeof(int)];
    int num_count, sum, i;

    // Create a socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);  // Convert IP address to binary format

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection to server failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }


    // Process command-line arguments
    num_count = argc - 1;
    for (i = 0; i < num_count; i++) {
        nums[i] = atoi(argv[i + 1]);  // Convert strings to integers
    }

    // Send the integers to the server
    send(client_fd, nums, num_count * sizeof(int), 0);

    // Receive the sum from the server
    recv(client_fd, &sum, sizeof(sum), 0);
    printf("from server: %d\n", sum);

    // Close the connection
    close(client_fd);
    return 0;
}

