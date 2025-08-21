#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>


#define THREAD_NUM 16

sem_t semaphore;


void * routine (void* args)
{
    printf("(%d) Waiting in the login Queue\n", *(int*)args);
    sem_wait(&semaphore);
    printf("(%d) Logged in\n",*(int*)args);
    sleep(rand() % 5 + 1);
    printf("(%d) Logged out\n",*(int*)args);
    sem_post(&semaphore);
    free(args);
}


void main(void) 
{
    pthread_t th[THREAD_NUM];

    sem_init(&semaphore , 0 , 8);

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