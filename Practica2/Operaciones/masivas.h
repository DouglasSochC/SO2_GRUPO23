#ifndef MASIVAS_H
#define MASIVAS_H
#include <cjson/cJSON.h>
#include "../Estructuras/usuario.h"
#include "../Estructuras/operacion.h"
#include "../Estructuras/error.h"

// Publica
void cargaMasivaUsuarios();
void cargarOperaciones(Operacion *operaciones, int *cantidadOperaciones);

// Privada
void *lecturaArchivoUsuarios(void *arg);
void validarUsuario(int fila, cJSON *numCuenta, cJSON *nombre, cJSON *saldo);
void crearArchivoLogUsuarios();
void escribirEnArchivo(char *nombreArchivo, char *texto);

#endif // MASIVAS_H