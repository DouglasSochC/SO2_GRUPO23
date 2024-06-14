#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Operaciones/individuales.h"
#include "Operaciones/masivas.h"
#include "Reportes/reporte.h"

void realizarOperacionIndividual();
void menu();

// Variables globales para almacenar usuarios y operaciones
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
        printf("5. Generar reporte de carga de usuarios\n");
        printf("6. Generar reporte de carga de operaciones\n");
        printf("7. Salir");
        printf("\n-------------------------------------------\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            cargarUsuarios(&cantidadUsuarios, usuarios);
            break;
        case 2:
            cargarOperaciones(&cantidadOperaciones, operaciones);
            break;
        case 3:
            realizarOperacionIndividual();
            break;
        case 4:
            generarReporteCuentas();
            break;
        case 5:
            generarReporteCargaUsuarios();
            break;
        case 6:
            generarReporteCargaOperaciones();
            break;
        case 7:
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\nOpción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 7);
}

// Función para realizar una operación individual
void realizarOperacionIndividual()
{

    int tipoOperacion;
    do
    {
        printf("\n--- OPERACION INDIVIDUAL ---\n");
        printf("1. Depósito\n");
        printf("2. Retiro\n");
        printf("3. Transferencia\n");
        printf("4. Consultar cuenta\n");
        printf("5. Volver al menu principal");
        printf("\n----------------------------\n");
        printf("Seleccione una operación: ");
        scanf("%d", &tipoOperacion);

        switch (tipoOperacion)
        {
        case 1:
            printf("\nLa opción seleccionada es: Depósito\n");
            break;
        case 2:
            printf("\nLa opción seleccionada es: Retiro\n");
            break;
        case 3:
            printf("\nLa opción seleccionada es: Transferencia\n");
            break;
        case 4:
            printf("\nLa opción seleccionada es: Consultar cuenta\n");
            break;
        case 5:
            printf("\n");
            break;
        default:
            printf("\nOpción no válida. Intente de nuevo.\n");
        }
    } while (tipoOperacion != 5);
}
