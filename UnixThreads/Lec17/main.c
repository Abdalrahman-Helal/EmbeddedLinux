#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


#define THREAD_NUM 2

void * routine (void* args)
{
    sleep(1);
    printf("Finished Execution \n");
}


void main(void) 
{
    pthread_t th[THREAD_NUM];
  
    int i; 
    for( i = 0; i < THREAD_NUM ; i++)
    {
       
        if( pthread_create(&th[i], NULL , &routine , NULL) != 0)
        {
            perror("Failed to Create Thread");
        }
        pthread_detach(th[i]);
    }
    pthread_exit(0);

}