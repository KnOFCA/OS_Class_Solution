#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int main() {
    HANDLE hReadPipe, hWritePipe;
    SECURITY_ATTRIBUTES sa;

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        perror("CreatePipe failed");
        return 1;
    }

    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdInput = hReadPipe;
    si.dwFlags |= STARTF_USESTDHANDLES;

    char* childProcess = (char*)"\"Solution_PipeC.exe\"";

    if (!CreateProcess(NULL, childProcess, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        perror("CreateProcess failed");
        return 1;
    }

    CloseHandle(pi.hThread);
    CloseHandle(hReadPipe);

    char input[BUFFER_SIZE];

    printf("input:");
    fgets(input, BUFFER_SIZE, stdin);

    input[strcspn(input, "\n")] = 0;

    DWORD written;
    WriteFile(hWritePipe, input, strlen(input) + 1, &written, NULL);
    CloseHandle(hWritePipe);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);

    return 0;
}
