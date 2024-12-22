#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>


void sigalrm_handler(int num)
{
    printf("SIGTSTP ignored\n");
}

void main()
{
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));          // Xóa sạch cấu trúc
    sa.sa_handler = sigalrm_handler;      // Gán hàm xử lý tín hiệu

    if (sigaction(SIGTSTP, &sa, NULL) == -1) {
        perror("Error setting up sigaction");
        exit(EXIT_FAILURE);
    }
#if 0
    if (signal(SIGTSTP , sigalrm_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }
#endif
    while (1)
    {
        sleep(1);
        printf("hello\n");
    }
}

