#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid)
    {
        // Proceso padre
        printf("Soy el proceso padre - %d\n", pid);
        printf("Mi PID es: %d\n\n", getpid());

        int status;
        wait(&status);

        if (WIFEXITED(status))
        {
            printf("\nEl proceso hijo termino con estado: %d\n", status);
        }
        else
        {
            printf("\nError: El proceso hijo termino con estado: %d\n", status);
        }

        printf("Terminando el proceso padre\n");
    }
    else
    {
        // Proceso hijo
        char *arg_Ptr[4];
        arg_Ptr[0] = " child.bin";
        arg_Ptr[1] = " Hola";
        arg_Ptr[2] = " Soy el proceso hijo! ";
        arg_Ptr[3] = NULL;

        execv("./child.bin", arg_Ptr);
    }
}