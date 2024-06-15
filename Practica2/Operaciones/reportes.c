#include "reportes.h"
#include <stdio.h>

void generarReporteCuentas(Usuario *usuarios, int cantidadUsuarios)
{
    for (int i = 0; i < cantidadUsuarios; i++)
    {
        printf("No. Cuenta: %d, Nombre: %s, Saldo: %.2f\n",
               usuarios[i].no_cuenta, usuarios[i].nombre, usuarios[i].saldo);
    }
}