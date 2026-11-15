#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

// Kept as 'empty' exactly as you wanted
sem_t empty; 
sem_t full;

pthread_mutex_t mutex;

void* producer(void* arg) 
{
    for (int item = 1; item <= ITEMS; item++) 
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        buffer[in] = item;
        std::cout << "Producer produced: " << item << std::endl;
        in = (in + 1) % BUFFER_SIZE;
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) 
{
    for (int i = 1; i <= ITEMS; i++) 
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        int item = buffer[out];
        std::cout << "Consumer consumed: " << item << std::endl;
        out = (out + 1) % BUFFER_SIZE;
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        
        sleep(2);
    }
    return NULL;
}

int main() 
{
    pthread_t producerThread, consumerThread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    std::cout << "\nProducer-Consumer execution completed." << std::endl;
    return 0;
}
