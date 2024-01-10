File Transfer App
=================

A simple client-server application to transfer files over the network using sockets in C++.

Requirements:
-------------
1. C++11 Compiler
2. CMake (Version 3.10 or higher)

Building and Running the Application:
-------------------------------------
1. Create a build directory:
    mkdir build && cd build

2. Generate makefiles using CMake:
    cmake path\to\homework_inter

3. Compile the code:
    make

4. Run the server:
    ./server

5. In a new terminal, run the client by specifying the file to transfer:
    ./client path\to\<filename>	or file name if it is in same folder

Notes:
------
- The server listens on port 8889 and writes the received file to "a.txt".
- The client connects to the server on the same port and sends the file provided as a command-line argument.
