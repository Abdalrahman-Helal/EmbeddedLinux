#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t stoveMutex[4];
int StoveFuel[4]= {100 , 100 , 100 , 100 } ;
 
void * Routine (void* args)
{
    for(int i = 0; i < 4; i++)
    {
        if ( pthread_mutex_trylock(&stoveMutex[i]) == 0 )
        {
            int FuelNeeded = (rand() % 30);
            if(StoveFuel[i] - FuelNeeded < 0)
            {
                printf(" No More Fuel. Going Home... \n");
            }
            
            else
            {
                StoveFuel[i] -= FuelNeeded ;
                usleep(500000);
                printf("Fuel Left %d \n" , StoveFuel[i]);
            }
            pthread_mutex_unlock(&stoveMutex[i]);
            break;
        }
        else
        {
            if (i == 3)
            {
                printf("No Stove Avaiable yet ,  Waiting... \n");
                usleep(300000);
                i=0;
            }
        }
    }

}


void main(void)
{
    srand(time(NULL));
    pthread_t th[10];
    for(int i = 0 ; i < 4 ; i ++)
    {
        pthread_mutex_init(&stoveMutex[i] , NULL);
    }


    for(int i = 0 ; i < 10 ; i++)
    {
        if( pthread_create(&th[i], NULL , &Routine , NULL) != 0)
        {
            perror("Failed to Create Thread");
        }
    }

    for(int i = 0 ; i < 10 ; i++)
    {
        if(pthread_join(th[i] ,NULL) != 0 )
        {
            perror("Erro at joining the Thread");
        }
    }

     for(int i = 0 ; i < 4 ; i ++)
    {
        pthread_mutex_destroy(&stoveMutex[i]);
    }


}