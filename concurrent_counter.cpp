//============================================================================
// Name        : Concurrent Counter Program
// Author      : FM
// Version     :
// Copyright   :
// Description : This program uses concurrency to create 2 threads, one
//               counting up to 20 and the second counting back down to 0,
//               while locking the mutex to maintain thread safety.
//============================================================================


#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter;

void countTo(int* start, int end, std::string counterName) {
    while (true) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << counterName << ": " << *start << std::endl;
        if (*start < end) {
            (*start)++;
        } else if (*start > end) {
        	(*start)--;
        } else {
            break;  // Exit the loop when start equals end
        }
    }
}

int main() {
    std::thread t1(countTo, &counter, 20, "thread 1 counter");
    t1.join();

    std::thread t2(countTo, &counter, 0, "thread 2 counter");
    t2.join();

    return 0;
}
