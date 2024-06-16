#include "reportes.h"
#include "../cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Necesario para isdigit()
#include <pthread.h>

// Función auxiliar para validar si un número es un entero
int esNumeroEntero(int numero)
{
    // Comprueba si el número es mayor o igual a cero
    // Esto también asegura que no sea un número negativo
    return (numero >= 0);
}

// Función para generar un reporte JSON del estado de cuentas
void generarReporteCuentas(Usuario *usuarios, int cantidadUsuarios)
{
    if (usuarios == NULL || cantidadUsuarios == 0)
    {
        printf("No hay usuarios disponibles para generar el reporte.\n");
        return;
    }

    // Crear el objeto raíz del JSON
    cJSON *reporteJSON = cJSON_CreateArray();

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        // Validar que el número de cuenta sea un dato entero y válido
        if (!esNumeroEntero(usuarios[i].no_cuenta))
        {
            continue; // Saltar al siguiente usuario
        }

        // Crear un objeto JSON para cada usuario
        cJSON *usuarioJSON = cJSON_CreateObject();
        cJSON_AddNumberToObject(usuarioJSON, "no_cuenta", usuarios[i].no_cuenta);
        cJSON_AddStringToObject(usuarioJSON, "nombre", usuarios[i].nombre);
        cJSON_AddNumberToObject(usuarioJSON, "saldo", usuarios[i].saldo);

        // Añadir el objeto de usuario al array principal
        cJSON_AddItemToArray(reporteJSON, usuarioJSON);
    }

    // Convertir el JSON a una cadena
    char *stringJSON = cJSON_Print(reporteJSON);
    if (stringJSON == NULL)
    {
        printf("Error al convertir el JSON a una cadena.\n");
        cJSON_Delete(reporteJSON);
        return;
    }

    // Obtener la hora actual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Crear una cadena para almacenar la fecha y hora formateada
    char fechaHora[20];

    // Formatear la fecha y hora
    snprintf(fechaHora, sizeof(fechaHora), "%04d_%02d_%02d-%02d_%02d_%02d",
             tm.tm_year + 1900, // Año
             tm.tm_mon + 1,     // Mes (0-11, por eso se suma 1)
             tm.tm_mday,        // Día del mes
             tm.tm_hour,        // Hora
             tm.tm_min,         // Minuto
             tm.tm_sec);        // Segundo
    char nombreReporte[100];
    sprintf(nombreReporte, "Reportes/estado_cuenta_%s.json", fechaHora);

    // Escribir el JSON en un archivo
    FILE *file = fopen(nombreReporte, "w");
    if (file == NULL)
    {
        printf("Error al abrir el archivo para escribir el reporte.\n");
        free(stringJSON);
        cJSON_Delete(reporteJSON);
        return;
    }

    fprintf(file, "%s\n", stringJSON);

    // Cerrar el archivo y liberar la memoria
    fclose(file);
    free(stringJSON);
    cJSON_Delete(reporteJSON);

    printf("Reporte generado exitosamente en '%s'.\n", nombreReporte);
}
