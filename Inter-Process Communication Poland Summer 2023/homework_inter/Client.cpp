#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    int client_socket;
    struct sockaddr_in server_addr;

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Could not create socket" << std::endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8889);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Could not connect to server. Error: " << strerror(errno) << std::endl;
        close(client_socket);
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    int size = file.tellg();
    file.seekg(0, std::ios::beg);
    char* fileBuffer = new char[size];
    file.read(fileBuffer, size);
    file.close();

    int err = send(client_socket, &size, sizeof(int), 0);
    if (err <= 0) {
        std::cerr << "send error: " << strerror(errno) << std::endl;
        delete[] fileBuffer;
        return 1;
    }
    printf("send %d bytes [OK]\n", err);

    err = send(client_socket, fileBuffer, size, 0);
    if (err <= 0) {
        std::cerr << "send error: " << strerror(errno) << std::endl;
    }
    printf("send %d bytes [OK]\n", err);

    delete[] fileBuffer;
    return 0;
}
