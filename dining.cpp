
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

pthread_t philosophers[N];
sem_t fork_sem[N];
sem_t room;

pthread_mutex_t print_mutex;

/* Philosopher function */
void *philosopher(void *arg)
{
    int id = *((int *)arg);

    // Thinking
    pthread_mutex_lock(&print_mutex);
    cout << "\nPhilosopher " << id << " is thinking...\n";
    pthread_mutex_unlock(&print_mutex);

    sleep(1);

    // Allow maximum N-1 philosophers to compete for forks
    sem_wait(&room);

    // Pick up left fork
    sem_wait(&fork_sem[id]);

    pthread_mutex_lock(&print_mutex);
    cout << "Philosopher " << id
         << " picked up left fork " << id << "\n";
    pthread_mutex_unlock(&print_mutex);

    // Pick up right fork
    sem_wait(&fork_sem[(id + 1) % N]);

    pthread_mutex_lock(&print_mutex);
    cout << "Philosopher " << id
         << " picked up right fork " << (id + 1) % N << "\n";
    pthread_mutex_unlock(&print_mutex);

    // Eating
    pthread_mutex_lock(&print_mutex);
    cout << "Philosopher " << id << " is eating...\n";
    pthread_mutex_unlock(&print_mutex);

    sleep(2);

    // Put down right fork
    sem_post(&fork_sem[(id + 1) % N]);

    // Put down left fork
    sem_post(&fork_sem[id]);

    pthread_mutex_lock(&print_mutex);
    cout << "Philosopher " << id
         << " finished eating.\n";
    cout << "----------------------------------------\n";
    pthread_mutex_unlock(&print_mutex);

    // Leave the room
    sem_post(&room);

    return NULL;
}

int main()
{
    int id[N];

    // Initialize print mutex
    pthread_mutex_init(&print_mutex, NULL);

    cout << "\n========================================\n";
    cout << "       DINING PHILOSOPHERS PROBLEM\n";
    cout << "========================================\n\n";

    // Initialize fork semaphores
    for (int i = 0; i < N; i++)
    {
        sem_init(&fork_sem[i], 0, 1);
    }

    // Allow only N-1 philosophers to try for forks
    sem_init(&room, 0, N - 1);

    // Create philosopher threads
    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &id[i]);
    }

    // Wait for philosopher threads
    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < N; i++)
    {
        sem_destroy(&fork_sem[i]);
    }

    sem_destroy(&room);

    // Destroy print mutex
    pthread_mutex_destroy(&print_mutex);

    cout << "\n========================================\n";
    cout << "       ALL PHILOSOPHERS FINISHED EATING\n";
    cout << "========================================\n\n";

    return 0;
}

