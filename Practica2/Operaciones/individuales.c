#include "individuales.h"
#include <stdio.h>

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

int deposito(Usuario *usuarios, int cantidadUsuarios)
{

    int no_cuenta;
    double monto;
    printf("\nIngrese el número de cuenta: ");
    scanf("%d", &no_cuenta);
    printf("\nIngrese el monto a depositar: ");
    scanf("%lf", &monto);

    if (monto <= 0)
    {
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

    return CUENTA_INEXISTENTE;
}

int retiro(Usuario *usuarios, int cantidadUsuarios)
{
    return EXITO;
    // int no_cuenta;
    // double monto;
    // printf("\n\nIngrese el número de cuenta: ");
    // scanf("%d", &no_cuenta);
    // printf("\n\nIngrese el monto a retirar: ");
    // scanf("%lf", &monto);

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
    return EXITO;
    // int cuenta_origen, cuenta_destino;
    // double monto;

    // printf("\n\nIngrese el número de cuenta de origen: ");
    // scanf("%d", &cuenta_origen);
    // printf("\n\nIngrese el número de cuenta de destino: ");
    // scanf("%d", &cuenta_destino);
    // printf("\n\nIngrese el monto a transferir: ");
    // scanf("%lf", &monto);

    // if (monto <= 0)
    // {
    //     printf("\nEl monto debe ser mayor a 0.\n");
    //     return;
    // }

    // Usuario *origen = NULL;
    // Usuario *destino = NULL;

    // for (int i = 0; i < numUsuarios; i++) {
    //     if (usuarios[i].no_cuenta == cuenta_origen) {
    //         origen = &usuarios[i];
    //     }
    //     if (usuarios[i].no_cuenta == cuenta_destino) {
    //         destino = &usuarios[i];
    //     }
    // }

    // if (origen == NULL) {
    //     printf("\nNúmero de cuenta de origen no encontrado.\n");
    //     return;
    // }

    // if (destino == NULL) {
    //     printf("\nNúmero de cuenta de destino no encontrado.\n");
    //     return;
    // }

    // if (origen->saldo >= monto) {
    //     origen->saldo -= monto;
    //     destino->saldo += monto;
    //     printf("\nTransferencia realizada. Nuevo saldo de la cuenta de origen: %.2f, cuenta de destino: %.2f\n\n", origen->saldo, destino->saldo);
    // } else {
    //     printf("\nSaldo insuficiente en la cuenta de origen.\n");
    // }
}

int consultarCuenta(Usuario *usuarios, int cantidadUsuarios)
{
    return EXITO;
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