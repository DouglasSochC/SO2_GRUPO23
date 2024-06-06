#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{

    pid_t pid = fork();

    if (pid)
    {
        printf("Soy el proceso padre \n");
    }
    else
    {
        printf("Soy el proceso hijo \n");
    }
}