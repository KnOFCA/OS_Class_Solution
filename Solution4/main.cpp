#include "Solution.h"
#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
#include <format>

const int NUM_SEATS = 100;
std::counting_semaphore sem_seats(NUM_SEATS);
std::vector<std::string> seat_registry(NUM_SEATS, "free");

static void EnterReadingRoom(const std::string& readerName) {
    sem_seats.acquire();
    int seatNumber = -1;

    for (int i = 0; i < NUM_SEATS; ++i) {
        if (seat_registry[i] == "free") {
            seat_registry[i] = readerName;
            seatNumber = i;
            break;
        }
    }

    std::cout << std::format("{} occupies seat {}.\n", readerName, seatNumber + 1);

    std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate reading

    seat_registry[seatNumber] = "free";
    sem_seats.release(); 
    std::cout << std::format("{} leaves seat {}.\n", readerName, seatNumber + 1);
}

int main() {
    std::vector<std::thread> readers;

    for (int i = 0; i < 200; ++i) { 
        readers.emplace_back(EnterReadingRoom, "Reader " + std::to_string(i + 1));
    }

    for (auto& reader : readers) {
        reader.join(); 
    }

    return 0;
}