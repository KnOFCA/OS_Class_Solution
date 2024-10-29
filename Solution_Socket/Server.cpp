#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    char buffer[1024] = { 0 };
    const char* hello = "Hello from server";

    // init Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }

    // create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return -1;
    }

    // set addr struct
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    // bind socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // lestion
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Waiting for connections..." << std::endl;

    // accept connection
    if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen)) == INVALID_SOCKET) {
        std::cerr << "Accept failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // send message
    send(clientSocket, hello, strlen(hello), 0);
    std::cout << "Hello message sent" << std::endl;

    // receive message
    int valread = recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Message from client: " << buffer << std::endl;

    // close socket
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
