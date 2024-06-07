#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define LOG_FILE "syscalls.log"
#define FILE_NAME "practica1.txt"

// Variables globales para contar las llamadas
int total_system_calls = 0;
int total_read_calls = 0;
int total_write_calls = 0;
int total_open_calls = 0;

// Función para manejar la senial del SIGINT (Ctrl + C)
void handle_sigint(int signum)
{
    printf("\n**********************\n");
    printf("\nSeñal SIGINT recibida\n");
    printf("\n**********************\n");
    printf("Número total de llamadas al sistema: %d\n", total_system_calls);
    printf("Número de llamadas al sistema por tipo (Read: %d, Write: %d, Open: %d)\n", total_read_calls, total_write_calls, total_open_calls);
    exit(0);
}

int main()
{

    // Manejador del SIGINT
    signal(SIGINT, handle_sigint);

    // Crear o vaciar el archivo de los logs
    FILE *log_file = fopen(LOG_FILE, "w");
    fclose(log_file);

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid)
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