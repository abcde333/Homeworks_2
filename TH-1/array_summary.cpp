#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>

using namespace std;

void sumArrayPart(const vector<int>& arr, int start, int end, atomic<long long>& partialSum) {
    long long sum = 0;
    for (int i = start; i < end; ++i) {
        sum += arr[i];
    }
    partialSum += sum;
}

long long sumArray(const vector<int>& arr) {
    long long sum = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }
    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./array-summary <N> <M>" << endl;
        return 1;
    }

    int N = stoi(argv[1]);
    int M = stoi(argv[2]);

    vector<int> arr(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 100);

    for (int i = 0; i < N; ++i) {
        arr[i] = dis(gen);
    }

    auto start = chrono::high_resolution_clock::now();
    sumArray(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationNoThreads = end - start;

    auto startThreads = chrono::high_resolution_clock::now();

    vector<thread> threads;
    atomic<long long> sumWithThreads(0);
    int blockSize = N / M;
    for (int i = 0; i < M; ++i) {
        int startIdx = i * blockSize;
        int endIdx = (i == M - 1) ? N : (i + 1) * blockSize;
        threads.push_back(thread(sumArrayPart, ref(arr), startIdx, endIdx, ref(sumWithThreads)));
    }

    for (auto& t : threads) {
        t.join();
    }

    auto endThreads = chrono::high_resolution_clock::now();
    chrono::duration<double> durationWithThreads = endThreads - startThreads;

    cout << "Time spent without threads: " << durationNoThreads.count() << " seconds" << endl;
    cout << "Time spent with " << M << " threads: " << durationWithThreads.count() << " seconds" << endl;

    return 0;
}
