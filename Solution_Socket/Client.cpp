#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET sock;
    sockaddr_in servAddr;
    char buffer[1024] = { 0 };
    const char* message = "Hello from client";

    // init Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }

    // create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return -1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8080);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect server
    if (connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    // send message
    send(sock, message, strlen(message), 0);
    std::cout << "Message sent from client" << std::endl;

    // receive message
    int valread = recv(sock, buffer, sizeof(buffer), 0);
    std::cout << "Message from server: " << buffer << std::endl;

    // close socket
    closesocket(sock);
    WSACleanup();

    return 0;
}
