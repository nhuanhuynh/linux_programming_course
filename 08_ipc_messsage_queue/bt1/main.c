#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <mqueue.h>



int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    struct mq_attr attr;

    // Đặt thuộc tính cho hàng đợi
    attr.mq_flags = 0;          // Không có chế độ non-blocking
    attr.mq_maxmsg = 10;        // Tối đa 10 tin nhắn trong hàng đợi
    attr.mq_msgsize = 1024; // Kích thước tối đa của mỗi tin nhắn
    attr.mq_curmsgs = 0;        // Số tin nhắn hiện tại (ban đầu là 0)

    // create queue
    mqd_t mqid = mq_open("/mqueue", O_RDWR | O_CREAT | O_NONBLOCK, 0644, &attr);
    if (mqid == -1) {  
        printf("mq_open() error\n");
        return -2;  
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    { /* Code executed by child */
        printf("[SON] PID is %d\n", getpid());
        char buffer[1024];

        // Nhận tin nhắn từ hàng đợi
        if (mq_receive(mqid, buffer, 1024, NULL) == -1) {
            perror("mq_receive failed");
            exit(EXIT_FAILURE);
        }

        printf("[SON] Received: %s\n", buffer);
        exit(EXIT_SUCCESS);
    }
    else
    { /* Code executed by parent */
        const char *message = "Hello SON!!!";

        printf("[DAD] Child PID is %d\n", getpid());

        if (mq_send(mqid, message, strlen(message) + 1, 0) == -1) {
            perror("mq_send failed");
            exit(EXIT_FAILURE);
        }

        // Unlink queue
        if (mq_unlink("/mqueue") == -1) 
        {
            perror("mq_unlink failed");
            exit(EXIT_FAILURE);
        }
    }
    // Close queue
    if (mq_close(mqid) == -1) 
    {
        perror("mq_close failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
