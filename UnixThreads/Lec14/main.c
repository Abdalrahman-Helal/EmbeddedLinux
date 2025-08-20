#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_barrier_t barrier;
void * Routine (void* args)
{
    // while(1)
    // {
        printf("Waiting for the Barrier... \n");
        sleep(1);
        pthread_barrier_wait(&barrier);
        printf("We passed the Barrier\n");
        sleep(1);
    // }

}


void main(void)
{
    pthread_t th[10];
    pthread_barrier_init(&barrier , NULL , 10 );
    
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

    pthread_barrier_destroy(&barrier);


}