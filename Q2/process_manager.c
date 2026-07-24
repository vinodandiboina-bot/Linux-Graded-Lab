#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_CHILDREN 5
#define TIMEOUT 3

void sigchld_handler(int sig) {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("[Parent] Child PID %d reaped. Exit status: %d\n", pid, WEXITSTATUS(status));
    }
}

int main() {
    pid_t pids[NUM_CHILDREN];
    struct sigaction sa;

    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    printf("[Parent] PID: %d — Creating %d child processes\n", getpid(), NUM_CHILDREN);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0) {
            printf("[Child %d] PID: %d started\n", i + 1, getpid());
            if (i == 2) {
                printf("[Child %d] PID: %d going unresponsive...\n", i + 1, getpid());
                sleep(30);
            } else {
                sleep(1);
            }
            printf("[Child %d] PID: %d finished\n", i + 1, getpid());
            exit(0);
        }
    }

    sleep(TIMEOUT);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        int status;
        pid_t result = waitpid(pids[i], &status, WNOHANG);

        if (result == 0) {
            printf("[Parent] Child PID %d unresponsive. Sending SIGTERM...\n", pids[i]);
            kill(pids[i], SIGTERM);
            sleep(1);
            result = waitpid(pids[i], &status, WNOHANG);
            if (result == 0) {
                printf("[Parent] Child PID %d still alive. Sending SIGKILL...\n", pids[i]);
                kill(pids[i], SIGKILL);
                waitpid(pids[i], &status, 0);
            }
        }
    }

    printf("[Parent] All children handled. Exiting cleanly.\n");
    return 0;
}
