#include "reader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PATH_SCRIPT "systemtap/memory_tracer.stp"

void execute_systemtap_script()
{
    // Variables auxiliares para ejecutar y obtener la informacion del systemtap
    char command[100];
    char buffer[128];
    FILE *fp;

    // Variables para la conexion a la base de datos
    const char *DB_HOST = getenv("DB_HOST");
    const char *DB_PORT = getenv("DB_PORT");
    const char *DB_USER = getenv("DB_USER");
    const char *DB_PASS = getenv("DB_PASS");
    const char *DB_NAME = getenv("DB_NAME");
    MYSQL *conn;

    int DB_PORT_INT = -1;
    if (DB_PORT != NULL)
    {
        DB_PORT_INT = atoi(DB_PORT);
    }
    else
    {
        printf("DB_PORT is not set\n");
        return;
    }

    // Variable que nos ayuda a identificar cuál es el tipo de operación que se está realizando
    char primer_caracter;

    // Inicializar conexión MySQL
    conn = mysql_init(NULL);
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT_INT, NULL, 0) == NULL)
    {
        fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // Comando para obtener la informacion del trace
    sprintf(command, "sudo stap %s", PATH_SCRIPT);

    // Abrir el comando para lectura
    fp = popen(command, "r");
    if (fp == NULL)
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Leer la salida del comando
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        // Atributos
        char timestamp[64], process[64], syscall_name[64];
        int pid, size;
        int acum = 0;

        // Auxiliares
        char delimitador[] = ",";
        char *token;

        // Obtener el primer token
        token = strtok(buffer, delimitador);

        // Recorrer el resto de los tokens
        while (token != NULL)
        {
            // Setear el timestamp
            if (acum == 0)
            {
                sprintf(timestamp, "%s", token);
            }
            // Setear el PID
            if (acum == 1)
            {
                pid = atoi(token);
            }
            // Setear el Process
            else if (acum == 2)
            {
                sprintf(process, "%s", token);
            }
            // Setear el Syscall
            else if (acum == 3)
            {
                sprintf(syscall_name, "%s", token);
            }
            // Setear el Size
            else if (acum == 4)
            {
                size = atoi(token);
            }
            acum++;
            token = strtok(NULL, delimitador);
        }

        insertarRegistro(conn, timestamp, pid, process, syscall_name, size);
    }

    // Se verifica si hubo un error al cerrar el comando
    if (pclose(fp) == -1)
    {
        perror("pclose");
        exit(EXIT_FAILURE);
    }
}

void insertarRegistro(MYSQL *conn, char *timestamp, int pid, char *process, char *syscall_name, int size)
{

    MYSQL_STMT *stmt;
    char query[1024];

    // Construir la consulta SQL para la inserción en la tabla procesos
    sprintf(query, "INSERT INTO procesos(pid, nombre_proceso, llamada, tamano_segmento, fecha_hora_solicitud) "
                   "VALUES(%d, '%s', '%s', %d, '%s')",
            pid, process, syscall_name, size, timestamp);

    // Preparar la consulta
    stmt = mysql_stmt_init(conn);
    if (!stmt)
    {
        fprintf(stderr, "mysql_stmt_init failed\n");
        return;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query)))
    {
        fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_error(conn));
        return;
    }

    // Ejecutar la consulta
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_stmt_error(stmt));
        return;
    }

    mysql_stmt_close(stmt);
}