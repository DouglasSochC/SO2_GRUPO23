#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

// Prototipos de funciones
void generar_y_guardar_caracteres(const char *nombre_archivo);
void leer_caracteres(const char *nombre_archivo);

int main(int argc, char *argv[])
{
    const char *nombre_archivo = argv[1];
    printf("Mi PID es: %d\n", getpid());

    srand(time(NULL)); // Inicializa el generador de números aleatorios

    while (1)
    {
        int tipo_llamada = rand() % 2;
        switch (tipo_llamada)
        {
        case 0:
        {
            generar_y_guardar_caracteres(nombre_archivo);
            break;
        }
        case 1:
        {
            leer_caracteres(nombre_archivo);
            break;
        }
        }
        int tiempo_espera = rand() % 3 + 1;
        sleep(tiempo_espera);
    }

    return 0;
}

// Función para generar y guardar 8 caracteres aleatorios en el archivo
void generar_y_guardar_caracteres(const char *nombre_archivo)
{
    FILE *archivo;
    archivo = fopen(nombre_archivo, "w"); // Modo append para añadir al final

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo para escribir");
        return;
    }

    for (int i = 0; i < 8; i++)
    {
        char caracter_aleatorio = 'A' + (rand() % 26); // Genera un carácter aleatorio entre 'A' y 'Z'
        fputc(caracter_aleatorio, archivo);
    }

    fclose(archivo);
}

// Función para leer y mostrar los primeros 8 caracteres del archivo
void leer_caracteres(const char *nombre_archivo)
{
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo para leer");
        return;
    }

    char buffer[9]; // Buffer para almacenar los caracteres leídos (8 caracteres + terminador nulo)
    size_t leidos = fread(buffer, sizeof(char), 8, archivo);
    buffer[leidos] = '\0'; // Añadir el terminador nulo al final

    fclose(archivo);
}
