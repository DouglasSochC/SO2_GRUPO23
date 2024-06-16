#include "individuales.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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

        switch (tipoOperacion)
        {
        case 1:
            deposito(usuarios, cantidadUsuarios);
            break;
        case 2:
            retiro(usuarios, cantidadUsuarios);
            break;
        case 3:
            transaccion(usuarios, cantidadUsuarios);
            break;
        case 4:
            consultarCuenta(usuarios, cantidadUsuarios);
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
        printf("Formato de número de cuenta inválido.\n");
        return OPERACION_NO_VALIDA;
    }

    // Solicitar monto
    printf("\nIngrese el monto a depositar: ");
    scanf("%s", input);

    if (esFlotante(input)) {
        monto = atof(input);
        printf("Formato de monto válido: %.2lf\n", monto);
    } else {
        printf("Formato de monto inválido.\n");
        return MONTO_NO_ES_NUMERO;
    }


    if (monto <= 0)
    {
        printf("\nEl monto ingresado debe ser mayor a 0. \n");
        return MONTO_ES_MENOR_A_0;
    }

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (usuarios[i].no_cuenta == no_cuenta)
        {
            usuarios[i].saldo += monto;
            printf("\nDepósito realizado. Nuevo saldo: %.2f\n\n", usuarios[i].saldo);
            return EXITO;
        }
    }
    printf("\nEl numero de cuenta %d no existe\n", no_cuenta);
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
        printf("Formato de número de cuenta inválido.\n");
        return OPERACION_NO_VALIDA;
    }

    // Solicitar monto
    printf("\nIngrese el monto a retirar: ");
    scanf("%s", input);

    if (esFlotante(input)) {
        monto = atof(input);
        printf("Formato de monto válido: %.2lf\n", monto);
    } else {
        printf("Formato de monto inválido.\n");
        return MONTO_NO_ES_NUMERO;
    }


    if (monto <= 0)
    {
        printf("\nEl monto ingresado debe ser mayor a 0. \n");
        return MONTO_ES_MENOR_A_0;
    }

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (usuarios[i].no_cuenta == no_cuenta)
        {
            if(usuarios[i].saldo < monto){
                printf("\nEl saldo de la cuenta %d, no es suficiente. Por lo tanto, no se puede efectuar el retiro.\n", no_cuenta);
                return SALDO_INSUFICIENTE;
            }
            usuarios[i].saldo -= monto;
            printf("\nRetiro realizado. Nuevo saldo: %.2f\n\n", usuarios[i].saldo);
            return EXITO;
        }
    }
    printf("\nEl numero de cuenta %d no existe\n", no_cuenta);
    return CUENTA_INEXISTENTE;
    
  
   

    // if (monto <= 0)
    // {
    //     printf("\nEl monto debe ser mayor a 0.\n");
    //     return;
    // }

    // for (int i = 0; i < numUsuarios; i++) {
    //     if (usuarios[i].no_cuenta == no_cuenta) {
    //         if (usuarios[i].saldo >= monto) {
    //             usuarios[i].saldo -= monto;
    //             printf("\nRetiro realizado. Nuevo saldo: %.2f\n", usuarios[i].saldo);
    //         } else {
    //             printf("\nSaldo insuficiente.\n");
    //         }
    //         return;
    //     }
    // }

    // printf("\nNúmero de cuenta no encontrado.\n");
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
        printf("Formato de número de cuenta de origen inválido. Debe ser un entero positivo.\n");
        return OPERACION_NO_VALIDA;
    }

    // Solicitar el número de cuenta de destino
    printf("\n\nIngrese el número de cuenta de destino: ");
    scanf("%s", input);

    if (esEntero(input)) {
        cuenta_destino = atoi(input);
        printf("Formato de número de cuenta de destino válido: %d\n", cuenta_destino);
    } else {
        printf("Formato de número de cuenta de destino inválido. Debe ser un entero positivo.\n");
        return OPERACION_NO_VALIDA; // Salir del programa por entrada inválida
    }

    // Solicitar el monto a transferir
    printf("\n\nIngrese el monto a transferir: ");
    scanf("%s", input);

    if (esFlotante(input)) {
        monto = atof(input);
        if (monto <= 0) {
            printf("\nEl monto debe ser mayor a 0.\n");
            return MONTO_ES_MENOR_A_0;
        } else {
            printf("Monto válido: %.2lf\n", monto);
        }
    } else {
        printf("Formato del monto inválido.\n");
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
        printf("\nNúmero de cuenta de origen %d no encontrado.\n", cuenta_origen);
        return CUENTA_INEXISTENTE;
    }

    if (destino == NULL) {
        printf("\nNúmero de cuenta de destino %d no encontrado.\n", cuenta_destino);
        return CUENTA_INEXISTENTE;
    }

    if (origen->saldo >= monto) {
        origen->saldo -= monto;
        destino->saldo += monto;
        printf("\nTransferencia realizada. Nuevo saldo de la cuenta de origen: %.2f, cuenta de destino: %.2f\n\n", origen->saldo, destino->saldo);
    } else {
        printf("\nSaldo insuficiente en la cuenta de origen.\n");
        return SALDO_INSUFICIENTE;
    }

    return EXITO;
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
        printf("Formato de número de cuenta inválido.\n");
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

    printf("\nEl numero de cuenta %d no existe\n", no_cuenta);
    return CUENTA_INEXISTENTE;
    
    // int no_cuenta;
    // printf("\nIngrese el número de cuenta: ");
    // scanf("%d", &no_cuenta);

    // for (int i = 0; i < numUsuarios; i++) {
    //     if (usuarios[i].no_cuenta == no_cuenta) {
    //         printf("\nNúmero de cuenta: %d\n", usuarios[i].no_cuenta);
    //         printf("Nombre: %s\n", usuarios[i].nombre);
    //         printf("Saldo: %.2f\n\n", usuarios[i].saldo);
    //         return;
    //     }
    // }

    // printf("\nNúmero de cuenta no encontrado.\n");
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