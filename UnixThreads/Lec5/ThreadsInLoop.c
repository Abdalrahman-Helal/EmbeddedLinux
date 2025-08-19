#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
int mails = 0;


void *routine(void)
{
    for(int i = 0; i < 1000000; i++)
    {   
        pthread_mutex_lock(&mutex);
        mails++; 
        pthread_mutex_unlock(&mutex);
    }
}


void main(void)
{
    pthread_t th[12];
    pthread_mutex_init(&mutex , NULL);
    for(int i = 0 ; i < 12; i++)
    {
        if(pthread_create(&th[i], NULL , routine , NULL) != 0)  
        {
           perror("Failed to Create Thread");
           return 1;
        }
        printf("Thread %d has started \n", i+1);
      
    }

    for(int i = 0 ; i < 12 ; i++)
    {
        if (pthread_join(th[i] , NULL) != 0)
        {
            return 2;   
        }
        printf("Thread %d has finished execution \n", i+1);
    }
    pthread_mutex_destroy(&mutex);
    printf("Numbers of Mails : %d \n",mails);
}