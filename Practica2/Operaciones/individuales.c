#include "individuales.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "../Estructuras/constantes.h"

extern Usuario *usuarios;
extern int cantidadUsuarios;

void menuOperacionIndividual()
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
        {
            char input[100];
            int no_cuenta;
            double monto;

            // Solicitar número de cuenta
            printf("Ingrese el número de cuenta: ");
            scanf("%s", input);
            // Se valida la entrada
            if (esEntero(input))
            {
                no_cuenta = atoi(input);
            }
            else
            {
                printf("La cuenta ingresada no es un número válido.\n");
                break;
            }

            // Solicitar monto
            printf("Ingrese el monto a depositar: ");
            scanf("%s", input);
            // Se valida la entrada
            if (esFlotante(input))
            {
                monto = atof(input);
            }
            else
            {
                printf("El monto ingresado no es un número válido.\n");
                break;
            }

            // Realizar procedimiento
            resultado = deposito(no_cuenta, monto);
            char *resMensajeOperacion = obtenerMensajeOperacion(resultado);
            printf("%s", resMensajeOperacion);
            break;
        }
        case 2:
        {
            char input[100];
            int no_cuenta;
            double monto;

            // Solicitar número de cuenta
            printf("Ingrese el número de cuenta: ");
            scanf("%s", input);
            // Se valida la entrada
            if (esEntero(input))
            {
                no_cuenta = atoi(input);
            }
            else
            {
                printf("La cuenta ingresada no es un número válido.\n");
                break;
            }

            // Solicitar monto
            printf("Ingrese el monto a depositar: ");
            scanf("%s", input);
            // Se valida la entrada
            if (esFlotante(input))
            {
                monto = atof(input);
            }
            else
            {
                printf("El monto ingresado no es un número válido.\n");
                break;
            }

            resultado = retiro(no_cuenta, monto);
            char *resMensajeOperacion = obtenerMensajeOperacion(resultado);
            printf("%s", resMensajeOperacion);
            break;
        }
        case 3:
        {
            char input[100];
            int cuenta_origen, cuenta_destino;
            double monto;

            // Solicitar el número de cuenta de origen
            printf("Ingrese el número de cuenta de origen: ");
            scanf("%s", input);
            // Se valida la entrada
            if (esEntero(input))
            {
                cuenta_origen = atoi(input);
            }
            else
            {
                printf("La cuenta ingresada no es un número válido.\n");
                break;
            }

            // Solicitar el número de cuenta de destino
            printf("Ingrese el número de cuenta de destino: ");
            scanf("%s", input);
            // Se valida la entrada
            if (esEntero(input))
            {
                cuenta_destino = atoi(input);
            }
            else
            {
                printf("La cuenta ingresada no es un número válido.\n");
                break;
            }

            // Solicitar el monto a transferir
            printf("Ingrese el monto a transferir: ");
            scanf("%s", input);
            // Se valida la entrada
            if (esFlotante(input))
            {
                monto = atof(input);
            }
            else
            {
                printf("El monto ingresado no es un número válido.\n");
                break;
            }
            resultado = transaccion(cuenta_origen, cuenta_destino, monto);
            char *resMensajeOperacion = obtenerMensajeOperacion(resultado);
            printf("%s", resMensajeOperacion);
            break;
        }
        case 4:
        {
            char input[100];
            int no_cuenta;

            // Solicitar número de cuenta
            printf("Ingrese el número de cuenta: ");
            scanf("%s", input);
            // Se valida la entrada
            if (esEntero(input))
            {
                no_cuenta = atoi(input);
            }
            else
            {
                printf("La cuenta ingresada no es un número válido.\n");
                break;
            }

            resultado = consultarCuenta(no_cuenta);
            char *resMensajeOperacion = obtenerMensajeOperacion(resultado);
            printf("%s", resMensajeOperacion);
            break;
        }
        default:
            printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (tipoOperacion != 5);
}

int deposito(int no_cuenta, double monto)
{
    if (monto <= 0)
    {
        return MONTO_ES_MENOR_A_0;
    }

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (usuarios[i].no_cuenta == no_cuenta)
        {
            usuarios[i].saldo += monto;
            return EXITO;
        }
    }
    return CUENTA_INEXISTENTE;
}

int retiro(int no_cuenta, double monto)
{
    if (monto <= 0)
    {
        return MONTO_ES_MENOR_A_0;
    }

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (usuarios[i].no_cuenta == no_cuenta)
        {
            if (usuarios[i].saldo < monto)
            {
                return SALDO_INSUFICIENTE;
            }
            usuarios[i].saldo -= monto;
            return EXITO;
        }
    }
    return CUENTA_INEXISTENTE;
}

int transaccion(int no_cuenta_origen, int no_cuenta_destino, double monto)
{
    Usuario *origen = NULL;
    Usuario *destino = NULL;

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (usuarios[i].no_cuenta == no_cuenta_origen)
        {
            origen = &usuarios[i];
        }
        if (usuarios[i].no_cuenta == no_cuenta_destino)
        {
            destino = &usuarios[i];
        }
    }

    if (origen == NULL)
    {
        return CUENTA_INEXISTENTE;
    }

    if (destino == NULL)
    {
        return CUENTA_INEXISTENTE;
    }

    if (monto <= 0)
    {
        return MONTO_ES_MENOR_A_0;
    }

    if (origen->saldo >= monto)
    {
        origen->saldo -= monto;
        destino->saldo += monto;
        return EXITO;
    }
    else
    {
        return SALDO_INSUFICIENTE;
    }
}

int consultarCuenta(int no_cuenta)
{
    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (usuarios[i].no_cuenta == no_cuenta)
        {
            printf("\nNúmero de cuenta: %d\n", usuarios[i].no_cuenta);
            printf("Nombre: %s\n", usuarios[i].nombre);
            printf("Saldo: %.2f\n\n", usuarios[i].saldo);
            return EXITO;
        }
    }
    return CUENTA_INEXISTENTE;
}

// Implementación de la función para verificar si una cadena es un número entero positivo
int esEntero(const char *cadena)
{
    if (*cadena == '-')
        return 0; // Rechazar si empieza con un signo negativo
    if (*cadena == '\0')
        return 0; // Cadena vacía no es un número válido

    while (*cadena)
    {
        if (!isdigit(*cadena))
            return 0;
        cadena++;
    }
    return 1;
}

// Implementación de la función para verificar si una cadena es un número flotante positivo
int esFlotante(const char *cadena)
{
    int puntoEncontrado = 0;

    if (*cadena == '-')
        return 0; // Rechazar si empieza con un signo negativo
    if (*cadena == '\0')
        return 0; // Cadena vacía no es un número válido

    while (*cadena)
    {
        if (*cadena == '.')
        {
            if (puntoEncontrado)
                return 0; // Más de un punto no es válido
            puntoEncontrado = 1;
        }
        else if (!isdigit(*cadena))
        {
            return 0;
        }
        cadena++;
    }
    return 1;
}

// Función que devuelve un mensaje basado en un código
char *obtenerMensajeOperacion(int codigo)
{
    char *mensaje = NULL;

    switch (codigo)
    {
    case EXITO:
    {
        const char *texto = "Operación realizada con éxito.";
        mensaje = (char *)malloc(strlen(texto) + 1);
        if (mensaje != NULL)
        {
            strcpy(mensaje, texto);
        }
        break;
    }
    case CUENTA_INEXISTENTE:
    {
        const char *texto = "El número de cuenta no existe.";
        mensaje = (char *)malloc(strlen(texto) + 1);
        if (mensaje != NULL)
        {
            strcpy(mensaje, texto);
        }
        break;
    }
    case MONTO_ES_MENOR_A_0:
    {
        const char *texto = "El monto ingresado debe ser mayor a 0.";
        mensaje = (char *)malloc(strlen(texto) + 1);
        if (mensaje != NULL)
        {
            strcpy(mensaje, texto);
        }
        break;
    }
    case SALDO_INSUFICIENTE:
    {
        const char *texto = "El saldo de la cuenta no es suficiente para realizar la operación.";
        mensaje = (char *)malloc(strlen(texto) + 1);
        if (mensaje != NULL)
        {
            strcpy(mensaje, texto);
        }
        break;
    }
    case OPERACION_NO_VALIDA:
    {
        const char *texto = "La operación no es válida.";
        mensaje = (char *)malloc(strlen(texto) + 1);
        if (mensaje != NULL)
        {
            strcpy(mensaje, texto);
        }
        break;
    }
    default:
    {
        const char *texto = "Código de operación desconocido.";
        mensaje = (char *)malloc(strlen(texto) + 1);
        if (mensaje != NULL)
        {
            strcpy(mensaje, texto);
        }
        break;
    }
    }

    return mensaje;
}