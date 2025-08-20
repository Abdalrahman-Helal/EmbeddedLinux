#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 8 

int DiceValues[8];
int status[8]= {0};


pthread_barrier_t barrierRolledRice;
pthread_barrier_t barrierCalculated;

void * RollDice (void* args)
{
    int Index = *(int *)args;
    DiceValues[Index] = rand() % 6 + 1 ;
    pthread_barrier_wait(&barrierRolledRice);
    pthread_barrier_wait(&barrierCalculated);

    if(status[Index] == 1)
    {
        printf(" (%d Rolled %d) I won \n" , Index, DiceValues[Index]);
    }
    else
    {
        printf(" (%d Rolled %d) I Lost \n" , Index, DiceValues[Index]);
        
    }
    free(args);
}


void main(void) 
{
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_barrier_init(&barrierRolledRice, NULL , THREAD_NUM +1);
    pthread_barrier_init(&barrierCalculated, NULL , THREAD_NUM +1);
    int i; 
    for( i = 0; i < THREAD_NUM ; i++)
    {
        int * a = malloc(sizeof(int));
        *a = i ;
        if( pthread_create(&th[i], NULL , &RollDice , a) != 0)
        {
            perror("Failed to Create Thread");
        }
    }
    pthread_barrier_wait(&barrierRolledRice);
    // Calaculate the Winner
    int max = 0 ; 
    for(i = 0 ; i < THREAD_NUM ; i++)
    {
        if(DiceValues[i] > max)
        {
            max= DiceValues[i];
        }
    }

    for(i = 0 ; i < THREAD_NUM ; i++)
    {
        if(DiceValues[i] == max)
        {
           status[i] = 1;
        }
        else
        {
            status[i] = 0;
        }
    }
    pthread_barrier_wait(&barrierCalculated);

    for(i = 0 ; i < THREAD_NUM ; i++)
    {
        if(pthread_join(th[i] ,NULL) != 0 )
        {
            perror("Erro at joining the Thread");
        }
    }

    pthread_barrier_destroy(&barrierRolledRice);
    pthread_barrier_destroy(&barrierCalculated);


}