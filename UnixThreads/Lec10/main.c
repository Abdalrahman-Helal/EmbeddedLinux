#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>


int Fuel = 0 ;
pthread_mutex_t MutexFuel;

pthread_cond_t CondFuel;

void * Fuel_Filling(void* arg)
{
    for(int i = 0 ; i < 5 ; i++)
    {
        pthread_mutex_lock(&MutexFuel);
        Fuel +=15;
        printf("Filling Fuel %d \n" , Fuel);
        pthread_mutex_unlock(&MutexFuel);
        pthread_cond_signal(&CondFuel);
        sleep(1);
    }
}
 
void * Car (void* arg)
{
    pthread_mutex_lock(&MutexFuel);
    while( Fuel < 40 )
    {
        printf("No Fuel . Waiting...\n");
        pthread_cond_wait(&CondFuel , &MutexFuel);
        // Equivelant to : 
        // pthread_mutex_unlock(&MutexFuel);
        // wait for singal ob  CondFuel 
        // pthread_mutex_lock(&MutexFuel);
    }

    Fuel -=40;
    printf("Got Fuel . Now Left %d \n",Fuel);
    pthread_mutex_unlock(&MutexFuel);
    
}


void main(void)
{
    pthread_t th[2];
    pthread_mutex_init(&MutexFuel , NULL);
    pthread_cond_init(&CondFuel, NULL);

    for(int i = 0 ; i < 2 ; i++)
    {
        if (i == 1)
        {
            if( pthread_create(&th[i], NULL , &Fuel_Filling , NULL) != 0)
            {
                perror("Failed to Create Thread");
            }
        }
        else
        {
             if( pthread_create(&th[i], NULL , &Car , NULL) != 0)
            {
                perror("Failed to Create Thread");
            }
        }
       
    }

    for(int i = 0 ; i < 2 ; i++)
    {
        if(pthread_join(th[i] ,NULL) != 0 )
        {
            perror("Erro at joining the Thread");
        }
    }

    pthread_mutex_destroy(&MutexFuel);
    pthread_cond_destroy(&CondFuel);

     
}