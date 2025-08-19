#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2, 3 , 5 , 7 , 11, 13 , 17 , 19 , 23 , 29};

void * routine(void * arg)
{
    int index = *(int*)arg;
    int sum = 0 ;
    for (int j= 0 ; j< 5; j++) 
    {
        sum += primes[index + j];
    }
    printf("Local Sum : %d\n", sum);
    *(int*)arg = sum;
    return arg;
}

void main(void)
{
    pthread_t th[2];
    int i ; 
    for(i = 0 ; i < 2 ; i++)
    {
        int * a = malloc(sizeof(int));
        *a = i * 5 ;
        if( pthread_create(&th[i], NULL , &routine , a) != 0)
        {
            perror("Failed to Create Thread");
        }
    }

    int GlobalSum = 0;
    for(i = 0 ; i < 2 ; i++)
    {
        int* res ; 
        if(pthread_join(th[i] ,(void**) &res) != 0 )
        {
            perror("Failed to Join Thread");
        }
        GlobalSum += *res;
        free(res);
    }
    
     printf("Total Sum is %d",GlobalSum);
}