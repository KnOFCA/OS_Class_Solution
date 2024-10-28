#include "Solution.h"
#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
#include <format>

std::binary_semaphore semA_C(1); // semaphore for A and C
std::binary_semaphore semB_D(1); // semaphore for B and D

// There's problem when pushing strings to output stream: chars out of order because group 1 and 2 don't lock each other.
// use format to connect string to fix that.
static void readFile(const char* processName, int group) {
    if (group == 1) { // A, C
        semA_C.acquire();
        std::cout << std::format("{} is reading the file.\n", processName);
        std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate reading
        std::cout << std::format("{} has finished reading.\n", processName);
        semA_C.release();
    }
    else if (group == 2) { // B, D
        semB_D.acquire();
        std::cout << std::format("{} is reading the file.\n", processName);
        std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate reading
        std::cout << std::format("{} has finished reading.\n", processName);
        semB_D.release();
    }
}

int main() {
    std::thread processA(readFile, "Process A", 1);
    std::thread processB(readFile, "Process B", 2);
    std::thread processC(readFile, "Process C", 1);
    std::thread processD(readFile, "Process D", 2);

    processA.join();
    processB.join();
    processC.join();
    processD.join();

    return 0;
}