#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room;
sem_t chopstick[5];

void eat(int phil)
{
    printf("\nPhilosopher %d is eating", phil);
    sleep(2); // Simulate eating
}

void *philosopher(void *num)
{
    int phil = *(int *)num;
    while (1)
    {
        // Philosopher thinks
        printf("\nPhilosopher %d is thinking", phil);
        sleep(2);

        // Request chopsticks
        printf("\nPhilosopher %d is hungry", phil);
        sem_wait(&room);
        sem_wait(&chopstick[phil]);
        sem_wait(&chopstick[(phil + 1) % 5]);

        // Philosopher eats
        eat(phil);

        // Release chopsticks
        sem_post(&chopstick[(phil + 1) % 5]);
        sem_post(&chopstick[phil]);
        sem_post(&room);
    }
}
int main()
{
    int i, a[5];
    pthread_t tid[5];

    sem_init(&room, 0, 4);
    for (i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);
    for (i = 0; i < 5; i++)
    {
        a[i] = i;
        pthread_create(&tid[i], NULL, philosopher, (void *)&a[i]);
    }
    for (i = 0; i < 5; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
