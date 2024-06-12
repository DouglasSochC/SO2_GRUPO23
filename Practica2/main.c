#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

// Prototipos de funciones
void cargarUsuarios();
void realizarOperacion();
void cargarOperaciones();
void generarReporteCuentas();
void generarReporteCargaUsuarios();
void generarReporteCargaOperaciones();
void menu();

void deposito();
void retiro();
void transferencia();
void consultarCuenta();

// Estructura de datos para las cuentas
typedef struct {
    int no_cuenta;
    char nombre[100];
    double saldo;
} Usuario;

// Estructura de datos para las operaciones
typedef struct {
    int operacion;
    int cuenta1;
    int cuenta2;
    double monto;
} Operacion;

// Variables globales para almacenar usuarios y operaciones
Usuario *usuarios = NULL;
int numUsuarios = 0;

Operacion *operaciones = NULL;
int numOperaciones = 0;

// Función principal
int main() {
    menu();
    return 0;
}

// Implementación del menú
void menu() {
    int opcion;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Carga masiva de usuarios\n");
        printf("2. Carga masiva de operaciones\n");
        printf("3. Realizar operación individual\n");
        printf("4. Generar reporte de estado de cuentas\n");
        printf("5. Generar reporte de carga de usuarios\n");
        printf("6. Generar reporte de carga de operaciones\n");
        printf("7. Salir\n\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                cargarUsuarios();
                break;
            case 2:
                cargarOperaciones();
                break;
            case 3:
                realizarOperacion();
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
    } while(opcion != 7);
}

// Función para cargar usuarios desde un archivo JSON simple
void cargarUsuarios() {
    char rutaArchivo[] = "usuarios.json";
    FILE *file = fopen(rutaArchivo, "r");
    if (file == NULL) {
        printf("\nNo se puede abrir el archivo %s.\n", rutaArchivo);
        return;
    }
    printf("\nCarga masiva de usuarios realizada desde %s.\n", rutaArchivo);
}

// Función para realizar una operación individual
void realizarOperacion() {
    int tipoOperacion;
    printf("\n--- Operaciones ---\n");
    printf("1. Depósito\n");
    printf("2. Retiro\n");
    printf("3. Transferencia\n");
    printf("4. Consultar cuenta\n");
    printf("5. Volver al menu principal\n\n");
    printf("Seleccione una operación: ");
    scanf("%d", &tipoOperacion);

    switch(tipoOperacion) {
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

    printf("\nOperación realizada.\n");
}

// Función para cargar operaciones masivamente
void cargarOperaciones() {
    char rutaArchivo[] = "operaciones.json";
    FILE *file = fopen(rutaArchivo, "r");
    if (file == NULL) {
        printf("\nNo se puede abrir el archivo %s.\n", rutaArchivo);
        return;
    }
    printf("\nCarga masiva de operaciones realizada desde %s.\n", rutaArchivo);
}

// Función para generar reporte de estado de cuentas (ejemplo)
void generarReporteCuentas() {
    // Aquí iría el código para generar el reporte de estado de cuentas
    printf("\nReporte de estado de cuentas generado.\n");
}

// Función para generar reporte de carga de usuarios (ejemplo)
void generarReporteCargaUsuarios() {
    // Aquí iría el código para generar el reporte de carga de usuarios
    printf("\nReporte de carga de usuarios generado.\n");
}

// Función para generar reporte de carga de operaciones (ejemplo)
void generarReporteCargaOperaciones() {
    // Aquí iría el código para generar el reporte de carga de operaciones
    printf("\nReporte de carga de operaciones generado.\n");
}

// Función para realizar un depósito
void deposito() {
    int no_cuenta;
    double monto;
    printf("\n\nIngrese el número de cuenta: ");
    scanf("%d", &no_cuenta);
    printf("\n\nIngrese el monto a depositar: ");
    scanf("%lf", &monto);

    if (monto <= 0) {
        printf("\nEl monto debe ser mayor a 0.\n");
        return;
    }

    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].no_cuenta == no_cuenta) {
            usuarios[i].saldo += monto;
            printf("\nDepósito realizado. Nuevo saldo: %.2f\n\n", usuarios[i].saldo);
            return;
        }
    }

    printf("\nNúmero de cuenta no encontrado.\n");
}

// Función para realizar un retiro
void retiro() {
    int no_cuenta;
    double monto;
    printf("\n\nIngrese el número de cuenta: ");
    scanf("%d", &no_cuenta);
    printf("\n\nIngrese el monto a retirar: ");
    scanf("%lf", &monto);

    if (monto <= 0) {
        printf("\nEl monto debe ser mayor a 0.\n");
        return;
    }

    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].no_cuenta == no_cuenta) {
            if (usuarios[i].saldo >= monto) {
                usuarios[i].saldo -= monto;
                printf("\nRetiro realizado. Nuevo saldo: %.2f\n", usuarios[i].saldo);
            } else {
                printf("\nSaldo insuficiente.\n");
            }
            return;
        }
    }

    printf("\nNúmero de cuenta no encontrado.\n");
}

// Función para realizar una transferencia
void transferencia() {
    int cuenta_origen, cuenta_destino;
    double monto;
    printf("\n\nIngrese el número de cuenta de origen: ");
    scanf("%d", &cuenta_origen);
    printf("\n\nIngrese el número de cuenta de destino: ");
    scanf("%d", &cuenta_destino);
    printf("\n\nIngrese el monto a transferir: ");
    scanf("%lf", &monto);

    if (monto <= 0) {
        printf("\nEl monto debe ser mayor a 0.\n");
        return;
    }

    Usuario *origen = NULL;
    Usuario *destino = NULL;

    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].no_cuenta == cuenta_origen) {
            origen = &usuarios[i];
        }
        if (usuarios[i].no_cuenta == cuenta_destino) {
            destino = &usuarios[i];
        }
    }

    if (origen == NULL) {
        printf("\nNúmero de cuenta de origen no encontrado.\n");
        return;
    }

    if (destino == NULL) {
        printf("\nNúmero de cuenta de destino no encontrado.\n");
        return;
    }

    if (origen->saldo >= monto) {
        origen->saldo -= monto;
        destino->saldo += monto;
        printf("\nTransferencia realizada. Nuevo saldo de la cuenta de origen: %.2f, cuenta de destino: %.2f\n\n", origen->saldo, destino->saldo);
    } else {
        printf("\nSaldo insuficiente en la cuenta de origen.\n");
    }
}

// Función para consultar una cuenta
void consultarCuenta() {
    int no_cuenta;
    printf("\nIngrese el número de cuenta: ");
    scanf("%d", &no_cuenta);

    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].no_cuenta == no_cuenta) {
            printf("\nNúmero de cuenta: %d\n", usuarios[i].no_cuenta);
            printf("Nombre: %s\n", usuarios[i].nombre);
            printf("Saldo: %.2f\n\n", usuarios[i].saldo);
            return;
        }
    }

    printf("\nNúmero de cuenta no encontrado.\n");
}