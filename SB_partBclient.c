#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8888

int main() {
    int clifd;
    struct sockaddr_in server_addr;

    // Create socket
    if ((clifd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address parameters
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(clifd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection has failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Retrieving random number from the server...\n");

    while (1) {
        char buffer[10];
        int num_bytes = recv(clifd, buffer, sizeof(buffer), 0);

        if (num_bytes <= 0) {
            printf("Server has disconnected.\n");
            break;
        }

        buffer[num_bytes] = '\0';
        int ran_num = atoi(buffer);

        printf("Received random number from server: %d\n", ran_num);
    }

    close(clifd);

    return 0;
}