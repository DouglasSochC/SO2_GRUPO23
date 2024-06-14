#include "individuales.h"
#include <stdio.h>

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

    // for (int i = 0; i < numUsuarios; i++) {
    //     if (usuarios[i].no_cuenta == no_cuenta) {
    //         usuarios[i].saldo += monto;
    //         printf("\nDepósito realizado. Nuevo saldo: %.2f\n\n", usuarios[i].saldo);
    //         return;
    //     }
    // }

    printf("\nNúmero de cuenta no encontrado.\n");
}

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

    printf("\nNúmero de cuenta no encontrado.\n");
}

void transaccion() {

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

void consultarCuenta() {

    int no_cuenta;
    printf("\nIngrese el número de cuenta: ");
    scanf("%d", &no_cuenta);

    // for (int i = 0; i < numUsuarios; i++) {
    //     if (usuarios[i].no_cuenta == no_cuenta) {
    //         printf("\nNúmero de cuenta: %d\n", usuarios[i].no_cuenta);
    //         printf("Nombre: %s\n", usuarios[i].nombre);
    //         printf("Saldo: %.2f\n\n", usuarios[i].saldo);
    //         return;
    //     }
    // }

    printf("\nNúmero de cuenta no encontrado.\n");
}