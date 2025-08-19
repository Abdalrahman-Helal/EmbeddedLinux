#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
int mails = 0;


void *routine(void)
{
    for(int i = 0; i < 10000000; i++)
    {   
        pthread_mutex_lock(&mutex);
        mails++; 
        pthread_mutex_unlock(&mutex);
    }
}


void main(void)
{
    pthread_t t1, t2 ,t3;
    pthread_mutex_init(&mutex , NULL);
    if(pthread_create(&t1, NULL , routine , NULL) != 0)  
    {
        return 1;
    }

    if(pthread_create(&t2, NULL , routine , NULL) != 0)  
    {
        return 2;
    }

    if(pthread_create(&t3, NULL , routine , NULL) != 0)  
    {
        return 3;
    }

    if (pthread_join(t1 , NULL) != 0)
    {
        return 4;
    }
    
    if (pthread_join(t2 , NULL) != 0)
    {
        return 5;
    }

    if (pthread_join(t3 , NULL) != 0)
    {
        return 6;
    }
    pthread_mutex_destroy(&mutex);
    printf("Numbers of Mails : %d \n",mails);
}