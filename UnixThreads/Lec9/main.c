#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t Mutex;

void * routine(void * arg)
{
    if (pthread_mutex_trylock(&Mutex) == 0 )
    {
        printf("Got Lock \n");
        pthread_mutex_unlock(&Mutex);
    }
    else
    {
        printf("Didn't Get Lock \n");
    }

}

void main (void)
{
    pthread_t th[4];
    pthread_mutex_init(&Mutex, NULL);
    for(int i = 0 ; i < 4 ; i++)
    {
        if( pthread_create(&th[i], NULL , &routine , NULL) != 0)
        {
            perror("Failed to Create Thread");
        }
    }

    for(int i = 0 ; i < 4 ; i++)
    {
        int* res ; 
        if(pthread_join(th[i] ,NULL) != 0 )
        {
            perror("Erro at joining the Thread");
        }
      
    }

}