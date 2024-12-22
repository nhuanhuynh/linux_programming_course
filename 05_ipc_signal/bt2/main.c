#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int signal_flag = 0;
int sigalrm_counter = 0;

void sigalrm_handler(int num)
{
    signal_flag = 1;
    sigalrm_counter++;
}

void main()
{

    if (signal(SIGALRM , sigalrm_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    alarm(1);

    while (1)
    {
        if (signal_flag)
        {
            printf("Timer: %d seconds\n", sigalrm_counter);
            if (sigalrm_counter == 10)
            {
                exit(EXIT_SUCCESS);
            }
            alarm(1);
            signal_flag = 0;
        }
    }
}

