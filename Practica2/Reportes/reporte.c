#include "reporte.h"
#include <stdio.h>

void generarReporteCuentas(Usuario *usuarios, int cantidadUsuarios)
{
    for (int i = 0; i < cantidadUsuarios; i++)
    {
        printf("No. Cuenta: %d, Nombre: %s, Saldo: %.2f\n",
               usuarios[i].no_cuenta, usuarios[i].nombre, usuarios[i].saldo);
    }
}

void generarReporteCargaUsuarios()
{
    // Aquí iría el código para generar el reporte de carga de usuarios
    printf("\nReporte de carga de usuarios generado.\n");
}

void generarReporteCargaOperaciones()
{
    // Aquí iría el código para generar el reporte de carga de operaciones
    printf("\nReporte de carga de operaciones generado.\n");
}
