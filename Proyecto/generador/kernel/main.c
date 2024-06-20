#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define LOG_FILE "../logs/memory_tracer.log"
#define SYSTEMTAP_SCRIPT "../systemtap/memory_tracer.stp"

// Función para crear el archivo de log
void create_log_file() {
    int fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error al crear el archivo de log");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Función para ejecutar el script de SystemTap
void execute_systemtap_script() {
    char command[256];
    snprintf(command, sizeof(command), "sudo stap %s > %s", SYSTEMTAP_SCRIPT, LOG_FILE);
    int status = system(command);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("El script de SystemTap se ejecutó correctamente.\n");
    } else {
        fprintf(stderr, "El script de SystemTap falló con estado %d.\n", WEXITSTATUS(status));
    }
}

// Función principal
int main() {
    // Crear el archivo de log
    create_log_file();
    printf("Archivo de log creado: %s\n", LOG_FILE);

    // Ejecutar el script de SystemTap
    execute_systemtap_script();

    return 0;
}
