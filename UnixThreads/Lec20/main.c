#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


#define THREAD_NUM 8

pthread_mutex_t mutexFuel;

int Fuel = 50; 


void * routine (void* args)
{
    pthread_mutex_lock(&mutexFuel);
    pthread_mutex_lock(&mutexFuel);
    Fuel+=50;
    printf("Icnrement Fuel to : %d\n" ,Fuel );
    pthread_mutex_unlock(&mutexFuel);
    pthread_mutex_unlock(&mutexFuel);

}


void main(void) 
{
    pthread_t th[THREAD_NUM];

    pthread_mutexattr_t recusiveMutexAttributes;
    pthread_mutexattr_init(&recusiveMutexAttributes);
    pthread_mutexattr_settype(&recusiveMutexAttributes , PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&mutexFuel , &recusiveMutexAttributes);
    int i; 
    for(i = 0; i < THREAD_NUM ; i++)
    {
        if( pthread_create(&th[i], NULL , &routine , NULL) != 0)
        {
            perror("Failed to Create Thread");
        }
    }

    for(i = 0; i < THREAD_NUM ; i++)
    {
        if( pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to Join Thread");
        }
    }
    printf("Fuel :%d \n" ,Fuel);
    pthread_mutexattr_destroy(&recusiveMutexAttributes);
    pthread_mutex_destroy(&mutexFuel);

}