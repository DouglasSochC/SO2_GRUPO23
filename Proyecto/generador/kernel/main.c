#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define SYSTEMTAP_SCRIPT "../systemtap/memory_tracer.stp"




// Función para ejecutar el script de SystemTap
void execute_systemtap_script() {
    char command[256];
    snprintf(command, sizeof(command), "sudo stap %s", SYSTEMTAP_SCRIPT);
    int status = system(command);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("El script de SystemTap se ejecutó correctamente.\n");
    } else {
        fprintf(stderr, "El script de SystemTap falló con estado %d.\n", WEXITSTATUS(status));
    }
}

// Función principal
int main() {
    // Ejecutar el script de SystemTap
    execute_systemtap_script();

    return 0;
}
