#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7000           // Port number for the server
#define BUFFER_SIZE 1024    // Buffer size for data transfer

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int nums[BUFFER_SIZE / sizeof(int)];
    int num_count, sum, i;

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Accept connections on any network interface
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 1) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

   

    // Accept a client connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd == -1) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }


    // Receive data from the client
    int received = recv(client_fd, buffer, BUFFER_SIZE, 0);
    if (received <= 0) {
        perror("Receive failed");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Convert received data to integers and display them
    num_count = received / sizeof(int);
    memcpy(nums, buffer, received);

    printf("from client: ");
    for (i = 0; i < num_count; i++) {
        printf("%d ", nums[i]);  // Print each number received from the client
    }
    printf("\n");

    // Calculate the sum of the numbers
    sum = 0;
    for (i = 0; i < num_count; i++) {
        sum += nums[i];
    }

    printf("server send %d\n", sum);

    // Send the sum back to the client
    send(client_fd, &sum, sizeof(sum), 0);

    // Close the connection
    close(client_fd);
    close(server_fd);
    return 0;
}

