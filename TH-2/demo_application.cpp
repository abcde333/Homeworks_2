#include <iostream>
#include <chrono>
#include "parallel_scheduler.h"

void example_function(int id) {
    std::cout << "Function " << id << " is being executed on thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    parallel_scheduler scheduler(3);  

    for (int i = 0; i < 10; ++i) {
        scheduler.run([i] { example_function(i); });
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
