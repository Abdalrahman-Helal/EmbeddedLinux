#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;

void *routine(void)
{
    for(int i = 0; i < 1000000; i++)
    {
        mails++; 
    }
}


void main(void)
{
    pthread_t t1, t2;
    if(pthread_create(&t1, NULL , routine , NULL) != 0)  
    {
        return 1;
    }

    if(pthread_create(&t2, NULL , routine , NULL) != 0)  
    {
        return 2;
    }

    if (pthread_join(t1 , NULL) != 0)
    {
        return 3;
    }
     if (pthread_join(t2 , NULL) != 0)
    {
        return 4;
    }
    printf("Numbers of Mails : %d \n",mails);
}