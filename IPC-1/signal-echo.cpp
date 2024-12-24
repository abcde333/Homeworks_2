#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstdlib>
#include <cstring>

using namespace std;

void signalHandler(int signum, siginfo_t *info, void *ucontext) {
    pid_t senderPID = info->si_pid;
    uid_t senderUID = info->si_uid;
    struct passwd *user = getpwuid(senderUID);

    cout << "Received a SIGUSR1 signal from process " << senderPID
         << " executed by " << senderUID << " (" 
         << (user ? user->pw_name : "unknown") << ")." << endl;
    

    cout << "State of the context: " 
         << "EIP = [simulated_value], EAX = [simulated_value], EBX = [simulated_value]." << endl;
}

int main() {
    cout << "PID of this process: " << getpid() << endl;

    struct sigaction sigAct;
    sigAct.sa_sigaction = signalHandler;
    sigAct.sa_flags = SA_SIGINFO;
    

    if (sigaction(SIGUSR1, &sigAct, NULL) == -1) {
        perror("Error registering signal handler");
        return 1;
    }


    while (true) {
        sleep(13);
    }

    return 0;
}
