#pragma once
#include <winsock2.h>

void socketDeleter1(SOCKET* socket) {
    closesocket(*socket);
    delete socket;
}

struct SocketDeleter2 {
    void operator()(SOCKET* socket) {
        closesocket(*socket);
        delete socket;
    }
};

auto socketDeleter3 = [](SOCKET* socket) {
    closesocket(*socket);
    delete socket;
    };
