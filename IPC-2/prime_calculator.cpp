#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <sstream>

using namespace std;

long long calculatePrime(int m) {
    if (m <= 1) return 2;
    int count = 1;
    long long num = 3;
    while (count < m) {
        bool isPrime = true;
        for (long long i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            count++;
        }
        num++;
    }
    return num - 1;
}

int main() {
    int pipe1[2], pipe2[2];
    string input;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        cerr << "Pipe creation failed!" << endl;
        return 1;
    }

    while (true) {
        cout << "[Parent] Please enter the number: ";
        getline(cin, input);

        if (input == "exit") {
            cout << "[Parent] Exiting program..." << endl;
            break;
        }

        int m;
        stringstream(input) >> m;

        if (stringstream(input) >> m) {
            pid_t pid = fork();

            if (pid == -1) {
                cerr << "Fork failed!" << endl;
                return 1;
            }

            if (pid == 0) {
                close(pipe1[1]);
                close(pipe2[0]);

                read(pipe1[0], &m, sizeof(m));
                close(pipe1[0]);

                cout << "[Child] Calculating " << m << "-th prime number..." << endl;
                long long result = calculatePrime(m);

                write(pipe2[1], &result, sizeof(result));
                close(pipe2[1]);

                return 0;
            } else {
                close(pipe1[0]);
                close(pipe2[1]);

                write(pipe1[1], &m, sizeof(m));
                close(pipe1[1]);

                cout << "[Parent] Sending " << m << " to the child process..." << endl;
                cout << "[Parent] Waiting for the response from the child process..." << endl;

                long long result;
                read(pipe2[0], &result, sizeof(result));
                close(pipe2[0]);

                cout << "[Parent] Received calculation result of prime(" << m << ") = " << result << "..." << endl;
                wait(NULL);
            }
        } else {
            cerr << "[Parent] Invalid input, please enter a valid number!" << endl;
        }
    }

    return 0;
}
