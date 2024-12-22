#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void func(int signum)
{
    printf("Func handler\n");
    wait(NULL);
}

int main(int argc, char *argv[])
{
    pid_t cpid;

    cpid = fork();

    if (cpid == 0)
    { /* Code executed by child */
        printf("Child PID is %d\n", getpid());
        while (1);
    }
    else
    { /* Code executed by parent */
        signal(SIGCHLD, func);
        printf("Parent PID is %d\n", getpid());
        while (1);
    }
}
