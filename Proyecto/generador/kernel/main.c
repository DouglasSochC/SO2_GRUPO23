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
    snprintf(command, sizeof(command), "sudo stap -g %s", SYSTEMTAP_SCRIPT);

    // Usar fork para crear un proceso hijo
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error al crear proceso hijo");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Proceso hijo creado exitosamente...\n");
        // Código del proceso hijo: ejecutar el script de SystemTap
        execl("/bin/sh", "sh", "-c", command, (char *) NULL);
        // Si execl falla
        perror("Error al ejecutar el script de SystemTap");
        exit(EXIT_FAILURE);
    } else {
        // Código del proceso padre: esperar a que el hijo termine
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("El script de SystemTap se ejecutó correctamente.\n");
        } else {
            fprintf(stderr, "El script de SystemTap falló con estado %d.\n", WEXITSTATUS(status));
        }
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
