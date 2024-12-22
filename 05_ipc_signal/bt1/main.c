#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int sigint_counter = 1;

void sigint_handler(int num)
{
    printf("SIGINT received\n");
    if (sigint_counter == 3)
    {
        exit(EXIT_SUCCESS);
    }
    sigint_counter++;
}

void main()
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // do nothing.
        printf("hello\n");
        sleep(1);
    }
}

