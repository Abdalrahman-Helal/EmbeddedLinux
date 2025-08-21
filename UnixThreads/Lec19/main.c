#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


#define THREAD_NUM 8

pthread_mutex_t mutexFuel;
pthread_mutex_t mutexWater;

int Fuel = 50;
int Water = 10;

void * routine (void* args)
{
    if(rand() % 2 == 0)
    {
        pthread_mutex_lock(&mutexFuel);
        sleep(1);
        pthread_mutex_lock(&mutexWater);
    }
    else
    {
        pthread_mutex_lock(&mutexWater);
        sleep(1);
        pthread_mutex_lock(&mutexFuel);
    }
    Fuel+=50;
    Water = Fuel; 
    printf("Icnrement Fuel to : %d  and Set Water to :%d \n" ,Fuel ,Water);
 
    pthread_mutex_unlock(&mutexFuel);
    pthread_mutex_unlock(&mutexWater);
}


void main(void) 
{
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexFuel , NULL);
    pthread_mutex_init(&mutexWater , NULL);
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
    printf("Water :%d \n" ,Water);
    pthread_mutex_destroy(&mutexFuel);
    pthread_mutex_destroy(&mutexWater);
}