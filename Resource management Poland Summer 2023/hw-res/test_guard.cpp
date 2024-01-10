#include "guard.h"
#include <iostream>
#include <Windows.h>

int main() {
    HANDLE hFile = CreateFile(
        "test.txt",              // file name
        GENERIC_WRITE,            // open for writing
        0,                        // do not share
        NULL,                     // default security
        CREATE_NEW,               // create new file only
        FILE_ATTRIBUTE_NORMAL,    // normal file
        NULL                      // no attribute template
    );
    {
        FileHandleGuard guard(hFile);
        std::cout << "File handle guarded.\n";
    } 

    return 0;
}
