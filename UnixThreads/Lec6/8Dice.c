#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void * RollDice()
{
    usleep(1000);
    int value = (rand() % 6) + 1; 
    int* result = malloc(sizeof(int));
    *result = value; 
    return (void *) result ; 
}

void main(void)
{
    int * res[8];
    srand(time(NULL));
    pthread_t th[8];
    for(int i = 0; i<8; i++)
    {
        if(pthread_create(&th[i] , NULL , &RollDice , NULL) != 0 )
        {
            perror("Failed to Create Thread ");
        }
    }

    for(int i = 0; i<8; i++)
    {
        if(pthread_join(th[i] , (void**) &res[i]) != 0)
        {
            return 2; 
        }
        printf("Thread %d has finished execution \n", i+1);
        printf("Result : %d\n" , *res[i]);
        free(res[i]);
    }
    
 

  
    return 0;

}
