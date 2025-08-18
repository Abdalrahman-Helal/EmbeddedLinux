#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void *routine(void)
{
    x+=5;
    sleep(2);
    printf("Value of x: %d \n", x);
}


void *routine2(void)
{
    sleep(2);
    printf("Value of x: %d \n", x);    
}


void main(void)
{
    pthread_t t1, t2;
    if(pthread_create(&t1, NULL , routine , NULL) != 0)  
    {
        return 1;
    }

    if(pthread_create(&t2, NULL , routine2 , NULL) != 0)  
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

}