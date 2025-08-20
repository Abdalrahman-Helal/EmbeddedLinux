#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>

#define THREAD_NUM 2

void * routine (void* args)
{
   pthread_t th=  pthread_self();
    printf(" %lu \n",th );
    printf("%d \n" ,(pid_t) syscall(SYS_gettid)) ;
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
    }
   
    for(i = 0 ; i < THREAD_NUM ; i++)
    {
        if(pthread_join(th[i] ,NULL) != 0 )
        {
            perror("Error at joining the Thread");
        }
    }

}