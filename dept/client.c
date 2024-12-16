#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080 // Same port number as the server
#define SERVER "127.0.0.1" // Server address (localhost)

int main(int argc, char *argv[]) {
    // Check if there are arguments (more than just the program name)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Join the command-line arguments into a single string
    char message[1024] = ""; // Empty buffer to concatenate arguments
    for (int i = 1; i < argc; i++) {
        strcat(message, argv[i]);
        if (i < argc - 1) {
            strcat(message, " "); // Add space between words
        }
    }

    // Send the string to the server
    send(sock, message, strlen(message), 0);

    // Receive the reversed string from the server
    int n = recv(sock, buffer, sizeof(buffer), 0);
    if (n < 0) {
        perror("Receive failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0'; // Add NULL terminator to the string

    // Print the reversed string
    printf("From Server: %s\n", buffer);

    // Close the socket
    close(sock);

    return 0;
}

