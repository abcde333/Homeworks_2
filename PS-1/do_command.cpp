#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>

void do_command(char** argv) {
    auto start_time = std::chrono::high_resolution_clock::now();

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Error: Failed to fork a process.\n";
        return;
    }

    if (pid == 0) {
        execvp(argv[0], argv); 
        perror("Error: execvp failed"); 
        exit(1); 
    } else {
        int status;
        waitpid(pid, &status, 0);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;

        if (WIFEXITED(status)) {
            std::cout << "Command completed with " << WEXITSTATUS(status)
                      << " exit code and took " << elapsed.count() << " seconds.\n";
        } else {
            std::cerr << "Command did not terminate successfully.\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./do-command <command> [args...]\n";
        return 1;
    }
    do_command(&argv[1]); 
    return 0;
}
