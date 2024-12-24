#include "parallel_scheduler.h"
#include <iostream>
#include <cassert>

parallel_scheduler::parallel_scheduler(size_t capacity)
    : stop(false)
{
    assert(capacity > 0);
    for (size_t i = 0; i < capacity; ++i) {
        workers.push_back(std::thread(&parallel_scheduler::worker_function, this));
    }
}

parallel_scheduler::~parallel_scheduler() {
    shutdown();
}

void parallel_scheduler::worker_function() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(tasks_mutex);
            cv.wait(lock, [this] { return stop || !tasks.empty(); });

            if (stop && tasks.empty()) return;

            task = tasks.front();
            tasks.pop();
        }

        task(); 
    }
}

void parallel_scheduler::run(std::function<void()> func) {
    {
        std::unique_lock<std::mutex> lock(tasks_mutex);
        tasks.push(func); 
    }
    cv.notify_one(); 
}

void parallel_scheduler::shutdown() {
    {
        std::unique_lock<std::mutex> lock(tasks_mutex);
        stop = true;
    }
    cv.notify_all(); 

    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}
