#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>


#define THREAD_NUM 4

pthread_mutex_t mutexFuel;
sem_t semFuel;


int Fuel = 50;

void * rouitne1 (void* args)
{
    while(1)
    {
        pthread_mutex_lock(&mutexFuel);
        Fuel += 50;
        printf("Current Value is %d \n", Fuel);
    }
   
}

void * rouitne2 (void* args)
{
    while(1)
    {
        pthread_mutex_unlock(&mutexFuel);
        usleep(5000);
    }
    
}



void main(void) 
{
  
    pthread_t th[THREAD_NUM];
    sem_init(&semFuel , 0 , 1);
    pthread_mutex_init(&mutexFuel , NULL);

    int i; 
    for(i = 0; i < THREAD_NUM ; i++)
    {
        if( i % 2 == 0 )
        {
            if( pthread_create(&th[i], NULL , &rouitne1 , NULL) != 0)
            {
                perror("Failed to Create Thread");
            }
        }
        else
        {
            if( pthread_create(&th[i], NULL , &rouitne2 , NULL) != 0)
            {
                perror("Failed to Create Thread");
            }
        }
    }

    for(i = 0; i < THREAD_NUM ; i++)
    {
        if( pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to Join Thread");
        }
    }
    
    sem_destroy(&semFuel);
    pthread_mutex_destroy(&mutexFuel);



}