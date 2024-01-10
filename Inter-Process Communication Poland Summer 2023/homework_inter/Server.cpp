#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Could not create socket" << std::endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8889);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Bind failed." << std::endl;
        close(server_socket);
        return 1;
    }

    if (listen(server_socket, 3) == -1) {
        std::cerr << "Listen failed." << std::endl;
        close(server_socket);
        return 1;
    }

    std::cout << "Waiting for incoming connections..." << std::endl;

    addr_len = sizeof(struct sockaddr_in);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
    if (client_socket == -1) {
        std::cerr << "Accept failed." << std::endl;
        close(server_socket);
        return 1;
    }

    int filesize = 0;
    int err = recv(client_socket, (char*)&filesize, sizeof(filesize), 0);
    if (err <= 0) {
        std::cerr << "recv error: " << strerror(errno) << std::endl;
        close(client_socket);
        close(server_socket);
        return 1;
    }
    printf("recv %d bytes [OK]\n", err);

    char* fileBuffer = new char[filesize];

    err = recv(client_socket, fileBuffer, filesize, MSG_WAITALL);  // Here, receive into fileBuffer
    if (err <= 0) {
        std::cerr << "recv error: " << strerror(errno) << std::endl;
        delete[] fileBuffer;
        close(client_socket);
        close(server_socket);
        return 1;
    }
    printf("recv %d bytes [OK]\n", err);

    std::ofstream file("a.txt", std::ios::binary);
    if(!file) {
        std::cerr << "File opening error." << std::endl;
        delete[] fileBuffer;
        close(client_socket);
        close(server_socket);
        return 1;
    }
    file.write(fileBuffer, filesize);
    file.close();

    delete[] fileBuffer;

    close(client_socket);
    close(server_socket);

    return 0;
}
