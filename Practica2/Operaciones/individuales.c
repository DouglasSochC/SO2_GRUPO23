#include "individuales.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "../Estructuras/constantes.h"

void menuOperacionIndividual(Usuario *usuarios, int cantidadUsuarios)
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

        int resultado;
        switch (tipoOperacion)
        {
        case 1:
            resultado = deposito(usuarios, cantidadUsuarios);
            imprimirMensajeOperacion(resultado);
            break;
        case 2:
            resultado = retiro(usuarios, cantidadUsuarios);
            imprimirMensajeOperacion(resultado);
            break;
        case 3:
            resultado = transaccion(usuarios, cantidadUsuarios);
            imprimirMensajeOperacion(resultado);
            break;
        case 4:
            resultado = consultarCuenta(usuarios, cantidadUsuarios);
            imprimirMensajeOperacion(resultado);
            break;
        case 5:
            printf("\n");
            break;
        default:
            printf("\nOpción no válida. Intente de nuevo.\n");
        }
    } while (tipoOperacion != 5);
}

int deposito(Usuario *usuarios, int cantidadUsuarios)
{
    char input[100];
    int no_cuenta;
    double monto;

    // Solicitar número de cuenta
    printf("\nIngrese el número de cuenta: ");
    scanf("%s", input);
    
    if (esEntero(input)) {
        no_cuenta = atoi(input);
        printf("Formato de número de cuenta válido: %d\n", no_cuenta);
    } else {
        return OPERACION_NO_VALIDA;
    }

    // Solicitar monto
    printf("\nIngrese el monto a depositar: ");
    scanf("%s", input);

    if (esFlotante(input)) {
        monto = atof(input);
    } else {
        return MONTO_NO_ES_NUMERO;
    }

    if (monto <= 0) {
        return MONTO_ES_MENOR_A_0;
    }

    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i].no_cuenta == no_cuenta) {
            usuarios[i].saldo += monto;
            printf("\nDepósito realizado. Nuevo saldo: %.2f\n\n", usuarios[i].saldo);
            return EXITO;
        }
    }
    return CUENTA_INEXISTENTE;
}

int retiro(Usuario *usuarios, int cantidadUsuarios)
{   
    char input[100];
    int no_cuenta;
    double monto;

    // Solicitar número de cuenta
    printf("\nIngrese el número de cuenta: ");
    scanf("%s", input);
    
    if (esEntero(input)) {
        no_cuenta = atoi(input);
        printf("Formato de número de cuenta válido: %d\n", no_cuenta);
    } else {
        return OPERACION_NO_VALIDA;
    }

    // Solicitar monto
    printf("\nIngrese el monto a retirar: ");
    scanf("%s", input);

    if (esFlotante(input)) {
        monto = atof(input);
    } else {
        return MONTO_NO_ES_NUMERO;
    }

    if (monto <= 0) {
        return MONTO_ES_MENOR_A_0;
    }

    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i].no_cuenta == no_cuenta) {
            if (usuarios[i].saldo < monto) {
                return SALDO_INSUFICIENTE;
            }
            usuarios[i].saldo -= monto;
            printf("\nRetiro realizado. Nuevo saldo: %.2f\n\n", usuarios[i].saldo);
            return EXITO;
        }
    }
    return CUENTA_INEXISTENTE;
}

int transaccion(Usuario *usuarios, int cantidadUsuarios)
{
    char input[100]; // Buffer para leer las entradas del usuario
    int cuenta_origen, cuenta_destino;
    double monto;

    // Solicitar el número de cuenta de origen
    printf("\n\nIngrese el número de cuenta de origen: ");
    scanf("%s", input);

    if (esEntero(input)) {
        cuenta_origen = atoi(input);
        printf("Formato de número de cuenta válido: %d\n", cuenta_origen);
    } else {
        return OPERACION_NO_VALIDA;
    }

    // Solicitar el número de cuenta de destino
    printf("\n\nIngrese el número de cuenta de destino: ");
    scanf("%s", input);

    if (esEntero(input)) {
        cuenta_destino = atoi(input);
        printf("Formato de número de cuenta válido: %d\n", cuenta_destino);
    } else {
        return OPERACION_NO_VALIDA;
    }

    // Solicitar el monto a transferir
    printf("\n\nIngrese el monto a transferir: ");
    scanf("%s", input);

    if (esFlotante(input)) {
        monto = atof(input);
        if (monto <= 0) {
            return MONTO_ES_MENOR_A_0;
        }
    } else {
        return MONTO_NO_ES_NUMERO;
    }

    Usuario *origen = NULL;
    Usuario *destino = NULL;

    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i].no_cuenta == cuenta_origen) {
            origen = &usuarios[i];
        }
        if (usuarios[i].no_cuenta == cuenta_destino) {
            destino = &usuarios[i];
        }
    }

    if (origen == NULL) {
        return CUENTA_INEXISTENTE;
    }

    if (destino == NULL) {
        return CUENTA_INEXISTENTE;
    }

    if (origen->saldo >= monto) {
        origen->saldo -= monto;
        destino->saldo += monto;
        printf("\nTransferencia realizada. Nuevo saldo de la cuenta de origen: %.2f, cuenta de destino: %.2f\n\n", origen->saldo, destino->saldo);
        return EXITO;
    } else {
        return SALDO_INSUFICIENTE;
    }
}

int consultarCuenta(Usuario *usuarios, int cantidadUsuarios)
{
    char input[100];
    int no_cuenta;

    // Solicitar número de cuenta
    printf("\nIngrese el número de cuenta: ");
    scanf("%s", input);
    
    if (esEntero(input)) {
        no_cuenta = atoi(input);
        printf("Formato de número de cuenta válido: %d\n", no_cuenta);
    } else {
        return OPERACION_NO_VALIDA;
    }

    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i].no_cuenta == no_cuenta) {
            printf("\nNúmero de cuenta: %d\n", usuarios[i].no_cuenta);
            printf("Nombre: %s\n", usuarios[i].nombre);
            printf("Saldo: %.2f\n\n", usuarios[i].saldo);
            return EXITO;
        }
    }
    return CUENTA_INEXISTENTE;
}

// Implementación de la función para verificar si una cadena es un número entero positivo
int esEntero(const char *cadena) {
    if (*cadena == '-') return 0; // Rechazar si empieza con un signo negativo
    if (*cadena == '\0') return 0; // Cadena vacía no es un número válido

    while (*cadena) {
        if (!isdigit(*cadena)) return 0;
        cadena++;
    }
    return 1;
}

// Implementación de la función para verificar si una cadena es un número flotante positivo
int esFlotante(const char *cadena) {
    int puntoEncontrado = 0;

    if (*cadena == '-') return 0; // Rechazar si empieza con un signo negativo
    if (*cadena == '\0') return 0; // Cadena vacía no es un número válido

    while (*cadena) {
        if (*cadena == '.') {
            if (puntoEncontrado) return 0; // Más de un punto no es válido
            puntoEncontrado = 1;
        } else if (!isdigit(*cadena)) {
            return 0;
        }
        cadena++;
    }
    return 1;
}

// Función para imprimir el mensaje correspondiente al código de retorno
void imprimirMensajeOperacion(int codigo) {
    switch (codigo) {
        case 0:
            printf("\nOperación realizada con éxito.\n");
            break;
        case 1:
            printf("\nEl número de cuenta no existe.\n");
            break;
        case 2:
            printf("\nEl monto ingresado no es un número válido.\n");
            break;
        case 3:
            printf("\nEl monto ingresado debe ser mayor a 0.\n");
            break;
        case 4:
            printf("\nEl saldo de la cuenta no es suficiente para realizar la operación.\n");
            break;
        case 5:
            printf("\nLa operación no es válida.\n");
            break;
        default:
            printf("\nCódigo de operación desconocido.\n");
            break;
    }
}