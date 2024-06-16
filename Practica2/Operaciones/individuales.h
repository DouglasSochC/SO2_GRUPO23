#ifndef INDIVIDUALES_H
#define INDIVIDUALES_H
#include "../Estructuras/usuario.h"
#include "../Estructuras/constantes.h"

/**
 * Todas las funciones retornan un entero que representa el resultado de la operación, clasificado en el archivo Estructuras/constantes.h
 */

void menuOperacionIndividual();
int deposito(int no_cuenta, double monto);
int retiro(int no_cuenta, double monto);
int transaccion(int no_cuenta_origen, int no_cuenta_destino, double monto);
int consultarCuenta(int no_cuenta);
// Función para verificar si una cadena es un número entero.
// Retorna 1 si la cadena representa un número entero válido, de lo contrario retorna 0.
int esEntero(const char *cadena);

// Función para verificar si una cadena es un número flotante.
// Retorna 1 si la cadena representa un número flotante válido, de lo contrario retorna 0.
int esFlotante(const char *cadena);
char *obtenerMensajeOperacion(int codigo);

#endif // INDIVIDUALES_H