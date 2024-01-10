#include <memory>       
#include <iostream>
#include <winsock2.h>
#include "delete_socket.h"

int main() {

    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }

    {
        SOCKET* testSocket = new SOCKET(); 
        std::unique_ptr<SOCKET, decltype(&socketDeleter1)> socket1(testSocket, socketDeleter1);
        std::cout << "Socket1 guarded.\n";
    }

    {
        SOCKET* testSocket = new SOCKET();
        std::unique_ptr<SOCKET, SocketDeleter2> socket2(testSocket);
        std::cout << "Socket2 guarded.\n";
    }

    {
        SOCKET* testSocket = new SOCKET();
        std::unique_ptr<SOCKET, decltype(socketDeleter3)> socket3(testSocket, socketDeleter3);
        std::cout << "Socket3 guarded.\n";
    }

    WSACleanup();
    return 0;
}
