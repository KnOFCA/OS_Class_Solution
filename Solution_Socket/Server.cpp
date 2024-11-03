#include <iostream>
#include <winsock2.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

SOCKET serverSocket = INVALID_SOCKET, clientSocket = INVALID_SOCKET;
std::vector<std::string> messages;
char inputBuffer[256] = "";


void startServer() {
    WSADATA wsaData;
    sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    const char* hello = "Hello from server";

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(serverSocket, SOMAXCONN);

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);

    send(clientSocket, hello, strlen(hello), 0);
}

void stopServer() {
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}

void sendMessage() {
    if (strlen(inputBuffer) > 0) {
        send(clientSocket, inputBuffer, strlen(inputBuffer), 0);
        messages.push_back("Client: " + std::string(inputBuffer));
        memset(inputBuffer, 0, sizeof(inputBuffer));
    }
}


void receiveMessages() {
    char buffer[1024] = { 0 };
    int valread = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (valread > 0) {
        messages.push_back("Client: " + std::string(buffer));
    }
}

void renderUI() {
    ImGui::Begin("Server");

    if (ImGui::Button("Start Server")) {
        startServer();
    }
    if (ImGui::Button("Stop Server")) {
        stopServer();
    }
    ImGui::InputText("Message", inputBuffer, sizeof(inputBuffer));
    if (ImGui::Button("Send Message")) {
        sendMessage();
    }

    if (ImGui::Button("Receive Message")) {
        receiveMessages();
    }

    ImGui::Text("Messages:");
    for (const auto& msg : messages) {
        ImGui::Text("%s", msg.c_str());
    }

    ImGui::End();
}

void initOpenGL() {
    if (!glfwInit())
        return;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui Server", NULL, NULL);
    glfwMakeContextCurrent(window);

    glViewport(0, 0, 1280, 720);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderUI();

        ImGui::Render();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    initOpenGL();
    return 0;
}
