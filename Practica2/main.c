#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Operaciones/individuales.h"
#include "Operaciones/masivas.h"
#include "Reportes/reporte.h"

void menu();

// Variables globales para almacenar usuarios y operaciones
Usuario *usuarios = NULL;
int cantidadUsuarios = 0;
Operacion *operaciones = NULL;
int cantidadOperaciones = 0;
pthread_mutex_t lock;

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
            pthread_mutex_init(&lock, NULL); // Inicializamos nuestro mutex
            pthread_t hilos[3];
            int ids[3] = {0, 1, 2};

            for (int i = 0; i < 3; i++)
            {
                pthread_create(&hilos[i], NULL, cargarUsuarios, &ids[i]);
            }

            for (int i = 0; i < 3; i++)
            {
                pthread_join(hilos[i], NULL);
            }
            pthread_mutex_destroy(&lock); // Liberamos los recursos del semaforo
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
