#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 100 000
// 0 -> 24999
// 25000 -> 49999
// 50000 -> 74999
// 75000 -> 99999

#define LENGTH 100000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int array[LENGTH];
int sum_i = 0;
int sum_refer = 0;
int sum_thread = 0;

static void *thread1_handler(void *args) 
{
    printf("Thread 1: Handler\n");

    for (int i = 0; i <= 24999; i++)
    {
        pthread_mutex_lock(&mutex);
        sum_thread += array[i];
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL); // exit
}
static void *thread2_handler(void *args) 
{
    printf("Thread 2: Handler\n");
    for (int i = 25000; i <= 49999; i++)
    {
        pthread_mutex_lock(&mutex);
        sum_thread += array[i];
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL); // exit
}
static void *thread3_handler(void *args) 
{
    printf("Thread 3: Handler\n");
    for (int i = 50000; i <= 74999; i++)
    {
        pthread_mutex_lock(&mutex);
        sum_thread += array[i];
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL); // exit
}
static void *thread4_handler(void *args) 
{
    printf("Thread 4: Handler\n");
    for (int i = 75000; i <= 99999; i++)
    {
        pthread_mutex_lock(&mutex);
        sum_thread += array[i];
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL); // exit
}

int main(int argc, char *argv[])
{
    int ret;
    pthread_t thread_id1;
    pthread_t thread_id2;
    pthread_t thread_id3;
    pthread_t thread_id4;

    for (int i = 0; i < LENGTH; i++)
    {
        array[i] = i;
        sum_refer += array[i];
    }

    if (ret = pthread_create(&thread_id1, NULL, &thread1_handler, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    if (ret = pthread_create(&thread_id2, NULL, &thread2_handler, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    if (ret = pthread_create(&thread_id3, NULL, &thread3_handler, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    if (ret = pthread_create(&thread_id4, NULL, &thread4_handler, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);
    pthread_join(thread_id4, NULL);

    printf("sum_refer:  %d\n", sum_refer);
    printf("sum_thread: %d\n", sum_thread);
    return 0;
}