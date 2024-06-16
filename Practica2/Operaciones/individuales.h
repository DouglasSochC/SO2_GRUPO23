#ifndef INDIVIDUALES_H
#define INDIVIDUALES_H
#include "../Estructuras/usuario.h"
#include "../Estructuras/constantes.h"

/**
 * Todas las funciones retornan un entero que representa el resultado de la operación, clasificado en el archivo Estructuras/constantes.h
 */

void menuOperacionIndividual(Usuario *usuarios, int cantidadUsuarios);
int deposito(Usuario *usuarios, int cantidadUsuarios);
int retiro(Usuario *usuarios, int cantidadUsuarios);
int transaccion(Usuario *usuarios, int cantidadUsuarios);
int consultarCuenta(Usuario *usuarios, int cantidadUsuarios);
// Función para verificar si una cadena es un número entero.
// Retorna 1 si la cadena representa un número entero válido, de lo contrario retorna 0.
int esEntero(const char *cadena);

// Función para verificar si una cadena es un número flotante.
// Retorna 1 si la cadena representa un número flotante válido, de lo contrario retorna 0.
int esFlotante(const char *cadena);
void imprimirMensajeOperacion(int codigo);

#endif // INDIVIDUALES_H