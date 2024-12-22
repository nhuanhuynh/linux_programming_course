#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// Child process handler
void handle_sigusr1(int signum) 
{
    printf("Child process received SIGUSR1 signal. signum: %d\n", signum);
}

int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork();

    if(pid == 0)
    {
        // Child process

        // callback register
        signal(SIGUSR1, handle_sigusr1);
        // wait for signal
        pause();
    }
    else 
    {
        // Parent process
        sleep(2);
        // send SIGUSR1 to child
        kill(pid, SIGUSR1);
        // wait for child terminate
        wait(NULL);
    }

    return 0;
}