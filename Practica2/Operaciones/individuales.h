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

#endif // INDIVIDUALES_H