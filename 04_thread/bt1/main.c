#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static void *handle_th1(void *args) 
{
    pthread_t thread_id = pthread_self();
    printf("Thread 1: Hello from thread: %lu\n", thread_id);
}

static void *handle_th2(void *args) 
{
    pthread_t thread_id = pthread_self();
    printf("Thread 2: Hello from thread: %lu\n", thread_id);
}


int main(int argc, char *argv[])
{
    int ret;
    pthread_t thread_id1, thread_id2;

    if (ret = pthread_create(&thread_id1, NULL, &handle_th1, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    if (ret = pthread_create(&thread_id2, NULL, &handle_th2, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    return 0;
}