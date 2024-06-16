#ifndef MASIVAS_H
#define MASIVAS_H
#include <cjson/cJSON.h>
#include <stdbool.h>
#include "../Estructuras/usuario.h"
#include "../Estructuras/operacion.h"
#include "../Estructuras/error.h"
#include "individuales.h"

// Publica
void cargaMasivaUsuarios();
void cargaMasivaOperaciones();

// Privada
void *lecturaArchivoUsuarios(void *arg);
void *lecturaArchivoOperaciones(void *arg);
void validarUsuario(int fila, cJSON *numCuenta, cJSON *nombre, cJSON *saldo);
bool validarOperacion(int fila, cJSON *operacion, cJSON *numCuentaOrigen, cJSON *numCuentaDestino, cJSON *monto);
void crearArchivoLogUsuarios();
void crearArchivoLogOperaciones();
void escribirEnArchivo(char *nombreArchivo, char *texto);

#endif // MASIVAS_H