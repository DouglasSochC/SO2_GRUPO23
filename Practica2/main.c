#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Operaciones/individuales.h"
#include "Operaciones/masivas.h"
#include "Operaciones/reportes.h"

void menu();

// Variables globales para gestionar a los usuarios
Usuario *usuarios = NULL;
int cantidadUsuarios = 0;
Operacion *operaciones = NULL;
int cantidadOperaciones = 0;

// Función principal
int main()
{
    menu();
    return 0;
}

// Implementación del menú
void menu()
{
    int opcion;
    do
    {
        printf("\n-------------- MENU PRINCIPAL -------------\n");
        printf("1. Carga masiva de usuarios\n");
        printf("2. Carga masiva de operaciones\n");
        printf("3. Realizar operación individual\n");
        printf("4. Generar reporte de estado de cuentas\n");
        printf("5. Salir");
        printf("\n-------------------------------------------\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            cargaMasivaUsuarios();
            break;
        case 2:
            cargarOperaciones(operaciones, &cantidadOperaciones);
            break;
        case 3:
            menuOperacionIndividual(usuarios, cantidadUsuarios);
            break;
        case 4:
            generarReporteCuentas(usuarios, cantidadUsuarios);
            break;
        case 5:
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\nOpción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 5);
}
