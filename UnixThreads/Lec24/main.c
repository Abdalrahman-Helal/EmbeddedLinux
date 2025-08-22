#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>


#define THREAD_NUM 1

sem_t semFuel;


int *Fuel ; 

void * rouitne (void* args)
{
   *Fuel += 50;
   printf("Current Value is %d \n", *Fuel);
   sem_post(&semFuel);
}



void main(void) 
{
  
    pthread_t th[THREAD_NUM];
    sem_init(&semFuel , 0 , 0);
    Fuel = malloc(sizeof(int));
    *Fuel = 50;
    int i; 
    for(i = 0; i < THREAD_NUM ; i++)
    {
        if( pthread_create(&th[i], NULL , &rouitne , NULL) != 0)
        {
            perror("Failed to Create Thread");
        }
    }

    sem_wait(&semFuel);
    printf("Deallocting Fuel \n");
    free(Fuel);
    for(i = 0; i < THREAD_NUM ; i++)
    {
        if( pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to Join Thread");
        }
    }
    
    sem_destroy(&semFuel);



}