#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void * RollDice()
{
    int value = (rand() % 6) + 1; 
    int* result = malloc(sizeof(int));
    *result = value; 
    printf("Thread Result : %p \n", result);
    return (void *) result ; 
}

void main(void)
{
    int * res ;
    srand(time(NULL));
    pthread_t th;
    if(pthread_create(&th , NULL , &RollDice , NULL) != 0 )
    {
        return 1; 
    }
    if(pthread_join(th , (void**) &res) != 0)
    {
        return 2; 
    }

    printf("Main Result : %p\n" , res);
    printf("Result : %d\n" , *res);
    free(res);
    return 0;

}
