#ifndef MASIVAS_H
#define MASIVAS_H
#include "../Estructuras/usuario.h"
#include "../Estructuras/operacion.h"

void cargarOperaciones(Operacion *operaciones, int *cantidadOperaciones);
void *cargarUsuarios(void *arg);

#endif // MASIVAS_H