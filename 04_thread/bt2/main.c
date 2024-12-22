#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static int counter = 0;

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;

static void *handle_th1(void *args) 
{
    pthread_t thread_id = pthread_self();
    printf("Thread 1: Hello from thread 1\n");

    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&lock1);
        counter++;
        pthread_mutex_unlock(&lock1);
    }
    printf("Thread 1: Increase counter DONE\n");
    pthread_exit(NULL); // exit
}

static void *handle_th2(void *args) 
{
    pthread_t thread_id = pthread_self();
    printf("Thread 2: Hello from thread 2\n");

    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&lock1);
        counter++;
        pthread_mutex_unlock(&lock1);
    }
    printf("Thread 2: Increase counter DONE\n");
    pthread_exit(NULL); // exit
}

static void *handle_th3(void *args) 
{
    pthread_t thread_id = pthread_self();
    printf("Thread 3: Hello from thread 3\n");

    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&lock1);
        counter++;
        pthread_mutex_unlock(&lock1);
    }
    printf("Thread 3: Increase counter DONE\n");
    pthread_exit(NULL); // exit
}


int main(int argc, char *argv[])
{
    int ret;
    pthread_t thread_id1, thread_id2, thread_id3;

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

    if (ret = pthread_create(&thread_id3, NULL, &handle_th3, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);

    printf("===> counter: %d\n", counter);


    return 0;
}