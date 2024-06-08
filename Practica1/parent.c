#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define LOG_FILE "syscalls.log"
#define SCRIPT_NAME "trace.stp"
#define FILE_NAME "practica1.txt"

// Variables globales para contar las llamadas
int total_system_calls = 0;
int total_read_calls = 0;
int total_write_calls = 0;

// Declaraciones de funciones
void crear_archivo(const char *nombre_archivo);
void eliminar_archivo(const char *nombre_archivo);
void handle_sigint(int signum);

// Función para manejar la señal del SIGINT (Ctrl + C)
void handle_sigint(int signum)
{
    
    // Obtener el SIGINT y parar el programa
    printf("\n**********************\n");
    printf("Señal SIGINT recibida\n");
    printf("**********************\n");
    printf("Número total de llamadas al sistema: %d\n", total_system_calls);
    printf("Número de llamadas al sistema por tipo (Read: %d, Write: %d)\n", total_read_calls, total_write_calls);
    exit(0);
}

// Función para crear y ejecutar un proceso hijo
pid_t create_and_exec_child(const char *program)
{
    pid_t pid = fork();

    // En el caso que haya un error durante el fork
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // Ejecución del hijo
    else if (pid == 0)
    {
        char *arg_Ptr[3];
        arg_Ptr[0] = (char *)program;
        arg_Ptr[1] = FILE_NAME;
        arg_Ptr[2] = NULL;
        execv(program, arg_Ptr);

        // Si execv falla
        perror("execv");
        exit(EXIT_FAILURE);
    }

    return pid;
}

int main()
{
    // Eliminar archivo txt
    eliminar_archivo(FILE_NAME);
    // Crear txt
    crear_archivo(FILE_NAME);

    // Manejador del SIGINT
    signal(SIGINT, handle_sigint);

    // Crear o vaciar el archivo de los logs
    FILE *log_file = fopen(LOG_FILE, "w");
    fclose(log_file);

    // Creación del hijo 1
    pid_t pid_1 = create_and_exec_child("child.bin");

    // Se realiza una espera para que cada proceso tenga acciones diferentes
    sleep(1);

    // Creación del hijo 2
    pid_t pid_2 = create_and_exec_child("child.bin");

    // Variables auxiliares para ejecutar y obtener la información del trace
    char command[100];
    char buffer[128];
    FILE *fp;

    // Variable auxiliar para almacenar los logs
    FILE *log_fp;

    // Variable que nos ayuda a identificar cuál es el tipo de operación que se está realizando
    char primer_caracter;

    // Comando para obtener la información del trace
    sprintf(command, "sudo stap %s %d %d", SCRIPT_NAME, pid_1, pid_2);

    // Abrir el comando para lectura
    fp = popen(command, "r");
    if (fp == NULL)
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Abrir el archivo syscalls.log para escritura
    log_fp = fopen(LOG_FILE, "a");
    if (log_fp == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Leer la salida del comando
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        // Obtener el primer caracter
        primer_caracter = buffer[0];

        // Identificación del tipo de operación
        if (primer_caracter == 'W')
        {
            total_write_calls++;
        }
        else if (primer_caracter == 'R')
        {
            total_read_calls++;
        }
        total_system_calls++;

        // Almacenando el log
        fprintf(log_fp, "%s", &buffer[1]);
    }

    // Cerrar el archivo syscalls.log
    if (fclose(log_fp) != 0)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    // Cerrar el archivo
    if (pclose(fp) == -1)
    {
        perror("pclose");
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid_1, &status, 0);
    waitpid(pid_2, &status, 0);

    return 0;
}

// Función para crear un archivo en la ruta actual
void crear_archivo(const char *nombre_archivo) {
    FILE *archivo;
    archivo = fopen(nombre_archivo, "w");

    if (archivo == NULL) {
        perror("Error al crear el archivo");
        return;
    }

    // Cierra el archivo después de crearlo
    fclose(archivo);
    
    printf("Archivo '%s' creado en la ruta actual.\n", nombre_archivo);
}

// Función para eliminar un archivo
void eliminar_archivo(const char *nombre_archivo) {
    // Intenta eliminar el archivo
    if (remove(nombre_archivo) == 0) {
        printf("Archivo '%s' eliminado exitosamente.\n", nombre_archivo);
    } else {
        perror("Error al eliminar el archivo");
    }
}
