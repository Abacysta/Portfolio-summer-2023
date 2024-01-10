#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <atomic>
#include <stdlib.h>
#include <string.h>
#include <iostream>


const int PORT = 8888;

std::atomic<int> client_count(0);

void* handle_client(void* arg) {
    int client_fd = *(int*)arg;
    const int bufferSize = 1024;
    bool is_running = true;
    while (is_running) {

        char buffer[bufferSize] = {};
        int bytes_received = read(client_fd, buffer, bufferSize);

        if (bytes_received <= 0) {
            std::cout << "connection closed or error from client: " << client_fd << "\n";
            is_running = false;
            break;
        }

        std::string message(buffer);
        std::cout << "message from client (fd: " << client_fd << ") = " << message << std::endl;

                if (message == "disconnect" || message == "Disconnect" || message == "DISCONNECT") {
            std::cout << "client (fd: " << client_fd << ") disconnected. " << std::endl;
            is_running = false;
            continue;
        } else if (message == "hello" || message == "Hello" || message == "HELLO") {
            std::string response = "world";
            send(client_fd, response.c_str(), response.length(), 0);
        } else {
            send(client_fd, buffer, bytes_received, 0);
        }
    }
    close(client_fd);
    client_count--;
    delete (int*)arg;
    return NULL;
}

void server() {
    int socket_fd;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cout << "unable to create socket \n";
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    int addr_len = sizeof(address);

    if (bind(socket_fd, (sockaddr*)&address, addr_len) == -1) {
        std::cout << "unable to bind socket \n";
        exit(EXIT_FAILURE);
    }

    if (listen(socket_fd, 5) == -1) {
        std::cout << "unable to listen\n";
        exit(EXIT_FAILURE);
    }
        std::cout << "Server started and waiting for connections...\n";
        pthread_t shutdown_thread;
    pthread_create(&shutdown_thread, NULL, [](void*) -> void* {
        while (true) {
            std::cout << "Type 'exit' to shut down the server (only works if no clients are connected).\n";
            std::string input;
            std::getline(std::cin, input);
            if (input == "exit" && client_count == 0) {
                exit(EXIT_SUCCESS);
            }
            if (client_count != 0) {
                std::cout << "Cannot shut down server. Clients are still connected.\n";
            }
        }
        return NULL;
    }, NULL);
    pthread_detach(shutdown_thread);


    while (true) {
            int client_fd;
            if ((client_fd = accept(socket_fd, (sockaddr*)&address, (socklen_t*)&addr_len)) == -1) {
                if(client_count == 0 ){
                    std::cout <<" Server is shutting down...\n";
                    break;
                }
                std::cout << "unable to accept connection\n";
                continue;
            }

            int* pclient = new int;
            *pclient = client_fd;
            client_count++;
            std::cout << "Connected client with fd: " << client_fd << std::endl;
            
            pthread_t thread_id;
            pthread_create(&thread_id, NULL, handle_client, pclient);
            pthread_detach(thread_id); 

        }
        // Cleanup main server socket
        close(socket_fd);
    }



void client() {
    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cout << "unable to create socket \n";
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Connect to localhost

    int addr_len = sizeof(address);

    if (connect(client_fd, (sockaddr*)&address, addr_len) < 0) {
        std::cout << "unable to connect\n";
        exit(EXIT_FAILURE);
    } 

    const int bufferSize = 1024;
    bool is_running = true;

    while (is_running) {
        std::cout << "Enter a message (or 'disconnect' to exit): ";
        std::string message;
        std::getline(std::cin, message);

        send(client_fd, message.c_str(), message.size(), 0);

        if (message == "disconnect" || message == "Disconnect" || message == "DISCONNECT") {
            is_running = false;
            continue;
        }

        char buffer[bufferSize] = {};
        int bytes_received = read(client_fd, buffer, bufferSize);
        if (bytes_received <= 0) {
            std::cout << "Server closed connection or an error occurred.\n";
            break;
        }
        std::cout << "Received from server: " << buffer << std::endl;
    }

    //clean-up
    close(client_fd);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "specify mode: server | client \n";
        exit(EXIT_FAILURE);
    }
    
    if (strcmp(argv[1], "server") == 0) {
        server();
    } else if (strcmp(argv[1], "client") == 0) {
        client();
    } else {
        std::cout << "Unknown mode specified\n";
        exit(EXIT_FAILURE);
    }


}
