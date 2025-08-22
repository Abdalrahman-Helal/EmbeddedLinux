#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>


#define THREAD_NUM 4

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

typedef struct Task
{
    void (*taskFunction)(int , int  );
    int arg1 , arg2;
} Task;

Task taskQueue [256];

int taskCount = 0;

void sum(int a , int b)
{   
    usleep(50000);
    int sum = a + b ;
    printf("Sum of %d and %d is %d\n", a, b, sum);
}

void prod(int a , int b)
{   
    usleep(50000);
    int prod = a * b ;
    printf("Product of %d and %d is %d\n", a, b, prod);
}

void sumAndProduct(int a, int b)
{
    int sum = a + b;
    int prod = a * b;

    printf("Sum and Product of %d and %d is %d and %d respectively \n" , a , b , sum , prod);

}

void executeTask(Task* task)
{
    task->taskFunction(task->arg1 , task->arg2);
}

void submitTask(Task task)
{
    usleep(50000);
    pthread_mutex_lock(&mutexQueue);
    taskQueue[taskCount] = task;
    taskCount++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}

void * startThread (void* args)
{
   while(1)
   {
        Task task; 

        pthread_mutex_lock(&mutexQueue);
        while(taskCount == 0 )
        {
            pthread_cond_wait(&condQueue ,&mutexQueue);
        }
          
        task =taskQueue[0];
        int i;
        for(i = 0; i < taskCount -1 ; i++)
        {
            taskQueue[i] = taskQueue[i+1];
        }
        taskCount--;
        
        pthread_mutex_unlock(&mutexQueue);
        executeTask(&task);
   }
}


void main(void) 
{
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexQueue , NULL);
    pthread_cond_init(&condQueue , NULL);

    int i; 
    for(i = 0; i < THREAD_NUM ; i++)
    {
        if( pthread_create(&th[i], NULL , &startThread , NULL) != 0)
        {
            perror("Failed to Create Thread");
        }
    }

    for(i=0 ; i < 100; i++)
    {
        Task t = {
            .taskFunction = i % 2 == 0? &sum : &prod,
            .arg1 = rand() % 100 ,
            .arg2 = rand() % 100
        };
        submitTask(t);
    }

    for(i = 0; i < THREAD_NUM ; i++)
    {
        if( pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to Join Thread");
        }
    }
    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&condQueue);
}