#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int ch_signal_counter = 0;

// Child process handler
void handle_sigusr1(int signum) 
{
    printf("Received signal from parent\n");
    ch_signal_counter++;
    if (ch_signal_counter == 5) {
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        // Child process
        // Register signal handler
        signal(SIGUSR1, handle_sigusr1);
        
        // Wait for signals
        while (1) {
            pause(); // Wait for SIGUSR1 signal
        }
    } 
    else if (pid > 0) {
        // Parent process
        for (int i = 0; i < 5; i++) {
            sleep(2);
            // Send SIGUSR1 to child
            kill(pid, SIGUSR1);
        }
        
        // Wait for child to terminate
        wait(NULL);
        printf("Parent: Child process terminated after receiving 5 signals.\n");
    } 
    else {
        // Fork failed
        perror("fork failed");
        return 1;
    }

    return 0;
}
