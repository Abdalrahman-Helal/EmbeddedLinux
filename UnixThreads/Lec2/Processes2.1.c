#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


void main (void)
{
    int pid = fork();

    if(pid == -1)
    {
        return 1;
    }
    printf("Hello From Processes \n");
    if(pid != 0 )
    {
        wait(NULL);
    }

}