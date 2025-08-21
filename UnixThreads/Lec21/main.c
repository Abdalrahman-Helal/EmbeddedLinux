#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>


#define THREAD_NUM 4

sem_t semaphore;


void * routine (void* args)
{
    sem_wait(&semaphore);
    sleep(1);
    printf("Hello From Thread %d \n",*(int*)args);
    sem_post(&semaphore);
    free(args);
}


void main(void) 
{
    pthread_t th[THREAD_NUM];

    sem_init(&semaphore , 0 , 3);

    int i; 
    for(i = 0; i < THREAD_NUM ; i++)
    {
        int *a = malloc(sizeof(int));
        *a =i;

        if( pthread_create(&th[i], NULL , &routine , a) != 0)
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
   sem_destroy(&semaphore);

}