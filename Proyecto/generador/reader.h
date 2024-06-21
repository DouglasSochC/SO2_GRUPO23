#ifndef READER_H
#define READER_H
#include <mysql/mysql.h>

// PUBLICO:
void execute_systemtap_script();

// PRIVADO:

// Función para insertar datos en la base de datos MySQL
void insertarRegistro(MYSQL *conn, char *timestamp, int pid, char *process, char *syscall_name, int size);

#endif // READER_H