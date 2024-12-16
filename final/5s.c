#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>  // For character conversion functions

#define PORT 9000 // Port number to be used (PORT >= 7000)
#define BACKLOG 10 // Maximum number of connections that can be queued



int main() {
  
    int server_fd, new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024];

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind server socket to address and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, BACKLOG) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }



    // Accept incoming connection from client
    if ((new_sock = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) == -1) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Receive data from client
    int n = recv(new_sock, buffer, sizeof(buffer), 0);
    if (n < 0) {
        perror("Receive failed");
        close(new_sock);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0'; // Add NULL terminator to the string



    // Send the modified string back to the client
    send(new_sock, buffer, strlen(buffer), 0);
    
    
    printf("From client: %s\n", buffer);
    
    while(1) {
    }
    
        // Close the socket
    close(server_fd);
    close(new_sock);
    
  




    return 0;
}

