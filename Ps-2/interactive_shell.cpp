#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void runShell() {
    std::string input;

    while (true) {
        std::cout << "enter the command: ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        std::vector<std::string> args;
        size_t pos = 0;
        while ((pos = input.find(' ')) != std::string::npos) {
            args.push_back(input.substr(0, pos));
            input.erase(0, pos + 1);
        }
        args.push_back(input);

        bool silentMode = (args[0] == "silent");
        if (silentMode) args.erase(args.begin());

        pid_t pid = fork();
        if (pid < 0) {
            std::cerr << "Fork failed!\n";
            continue;
        }

        if (pid == 0) { 
            if (silentMode) {
                int logFd = open(std::to_string(getpid()).c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(logFd, STDOUT_FILENO);
                dup2(logFd, STDERR_FILENO);
                close(logFd);
            }

            setenv("PATH", (std::string(getenv("PATH")) + ":.").c_str(), 1);

            std::vector<char*> c_args;
            for (auto& arg : args) {
                c_args.push_back(const_cast<char*>(arg.c_str()));
            }
            c_args.push_back(nullptr);

            execvp(c_args[0], c_args.data());
            std::cerr << "Command failed\n";
            exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

int main() {
    runShell();
    return 0;
}
