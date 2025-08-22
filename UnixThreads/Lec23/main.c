#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>


#define THREAD_NUM 2
pthread_mutex_t mutexBuffer;

sem_t semEmpty;
sem_t semFull;


int buffer[10];
int count = 0;

void * producer (void* args)
{
    while(1)
    {
        // Produce
        int x = rand() % 100 ; 
        
        // Add to the Buffer
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        buffer[count] = x ;
        count++;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
        
    }


}

void * consumer (void* args)
{
    while(1)    
    {
        int y;
        // Remove From the Buffer
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
      
        y  = buffer[count-1];
        count--;
       
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);
    
        // Consume 
        printf("Got %d \n", y);
        sleep(1);
    }
}


void main(void) 
{
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer , NULL);
    sem_init(&semEmpty , 0 , 10);
    sem_init(&semFull , 0 , 0);
    
    int i; 
    for(i = 0; i < THREAD_NUM ; i++)
    {
        if(i % 2 == 0)
        {
            if( pthread_create(&th[i], NULL , &producer , NULL) != 0)
            {
                perror("Failed to Create Thread");
            }
        }
        else
        {
              if( pthread_create(&th[i], NULL , &consumer , NULL) != 0)
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
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);


}