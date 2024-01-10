#pragma once
#include <Windows.h>

class FileHandleGuard {
private:
    HANDLE handle;

public:
    FileHandleGuard(HANDLE h) : handle(h) {}
    ~FileHandleGuard() {
        if (handle != INVALID_HANDLE_VALUE) {
            CloseHandle(handle);
        }
    }

    HANDLE get() const { return handle; }
};