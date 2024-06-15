#ifndef MASIVAS_H
#define MASIVAS_H
#include "../Estructuras/usuario.h"
#include "../Estructuras/operacion.h"

// Publica
void cargaMasivaUsuarios();
void cargarOperaciones(Operacion *operaciones, int *cantidadOperaciones);

// Privada
void *lecturaArchivoUsuarios(void *arg);
void crearArchivoLogUsuarios();
void escribirEnArchivo(char *nombreArchivo, char *texto);

#endif // MASIVAS_H