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

    // Se crea el primer hijo
    pid_t pid_1 = fork();

    // En el caso que haya un error durante el fork
    if (pid_1 == -1)
    {
        perror("fork");
        exit(1);
    }
    // Ejecucion del hijo
    else if (pid_1 == 0)
    {
        char *arg_Ptr[2];
        arg_Ptr[0] = "child.bin";
        arg_Ptr[1] = NULL;
        execv("./child.bin", arg_Ptr);
    }

    // Se realiza una espera para que cada proceso tenga acciones diferentes
    sleep(1);

    // Se crea el segundo hijo
    pid_t pid_2 = fork();

    // En el caso que haya un error durante el fork
    if (pid_2 == -1)
    {
        perror("fork");
        exit(1);
    }
    // Ejecucion del hijo
    else if (pid_2 == 0)
    {
        char *arg_Ptr[2];
        arg_Ptr[0] = "child.bin";
        arg_Ptr[1] = NULL;
        execv("./child.bin", arg_Ptr);
    }

    int status;
    waitpid(pid_1, &status, 0);
    waitpid(pid_2, &status, 0);
}