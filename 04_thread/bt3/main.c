#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int rand_number = 0;
static int data_ready = 0;

static void *producer(void *args) 
{
    pthread_t thread_id = pthread_self();
    // printf("Thread 1: Hello from producer\n");

    // for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);
        rand_number = rand() % 10 + 1;
        printf("Thread 1: Producer generated: %d\n", rand_number);
        data_ready = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        // sleep(1);
    }
    pthread_exit(NULL); // exit
}

static void *consummer(void *args) 
{
    pthread_t thread_id = pthread_self();
    // printf("Thread 2: Hello from consummer\n");

    // for (int i = 0; i < 10; i++)
    pthread_mutex_lock(&mutex);
    while (1)
    {
        // ready in advance when pthread_cond_signal() is called
        pthread_cond_wait(&cond, &mutex);
        // if (data_ready == 1)
        {
            printf("Thread 2: Global variable rand_number: %d.\n", rand_number);
            data_ready = 0;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL); // exit
}

int main(int argc, char *argv[])
{
    int ret;
    pthread_t thread_id1, thread_id2;

    srand(time(NULL));

    if (ret = pthread_create(&thread_id1, NULL, &producer, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    if (ret = pthread_create(&thread_id2, NULL, &consummer, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}