#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <functional>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

class parallel_scheduler {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex tasks_mutex;
    std::condition_variable cv;
    bool stop;

    void worker_function();

public:
    explicit parallel_scheduler(size_t capacity);
    ~parallel_scheduler();

    void run(std::function<void()> func);
    void shutdown();
};

#endif 
