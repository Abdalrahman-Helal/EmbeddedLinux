#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>


#define THREAD_NUM 4


sem_t sem;


int Fuel = 50;

void * rouitne (void* args)
{
    int Index = *(int*)args;
    int semVal; 
    sem_wait(&sem);
    sleep(Index +1);
    sem_getvalue(&sem , &semVal);
    printf("(%d) Curernt Semaphore value before wait is %d \n" , Index , semVal);
    sem_post(&sem);
    sem_getvalue(&sem , &semVal);
    printf("(%d) Curernt Semaphore value after post is %d \n" , Index , semVal);
    free(args);
}


void main(void) 
{
  
    pthread_t th[THREAD_NUM];
    sem_init(&sem , 0 , 4);
    int i; 
    for(i = 0; i < THREAD_NUM ; i++)
    {
        int * a = malloc(sizeof(int));
        *a = i ;
        if( pthread_create(&th[i], NULL , &rouitne , a) != 0)
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
    
    sem_destroy(&sem);




}