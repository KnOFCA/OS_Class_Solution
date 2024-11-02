#include <stdio.h>
#include <windows.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int main() {
    HANDLE hReadPipe = GetStdHandle(STD_INPUT_HANDLE);
    char buffer[BUFFER_SIZE];

    DWORD bytesRead;
    ReadFile(hReadPipe, buffer, BUFFER_SIZE, &bytesRead, NULL);
    buffer[bytesRead] = '\0';
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (isupper(buffer[i])) {
            buffer[i] = tolower(buffer[i]);
        }
        else if (islower(buffer[i])) {
            buffer[i] = toupper(buffer[i]);
        }
    }
    printf("converted:%s\n", buffer);

    return 0;
}
