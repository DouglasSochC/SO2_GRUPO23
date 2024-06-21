#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mysql/mysql.h>

#define LOG_FILE "../logs/memory_tracer.log"
#define DB_HOST "172.19.0.2" // Cambia esto por la IP del contenedor MySQL
#define DB_USER "proyecto1"
#define DB_PASS "proyecto1"
#define DB_NAME "proceso_db"

// Función para insertar datos en la base de datos MySQL
int insert_log_to_mysql(MYSQL *conn, char *timestamp, int pid, char *process, char *syscall_name, int size) {
    MYSQL_STMT *stmt;
    char query[1024];

    // Construir la consulta SQL para la inserción en la tabla procesos
    sprintf(query, "INSERT INTO procesos(pid, nombre_proceso, llamada, tamano_segmento, fecha_hora_solicitud) "
                   "VALUES(%d, '%s', '%s', %d, '%s')",
            pid, process, syscall_name, size, timestamp);

    // Preparar la consulta
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init failed\n");
        return 1;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_error(conn));
        return 1;
    }

    // Ejecutar la consulta
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_stmt_error(stmt));
        return 1;
    }

    mysql_stmt_close(stmt);

    return 0;
}

int main() {
    FILE *fp;
    char line[256];
    char timestamp[64], process[64], syscall_name[64];
    int pid, size;
    long int last_position = 0; // Variable para guardar la posición del último registro leído
    MYSQL *conn;

    // Inicializar conexión MySQL
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // Abrir y leer el archivo de log continuamente
    while (1) {
        fp = fopen(LOG_FILE, "r");
        if (fp == NULL) {
            fprintf(stderr, "Error al abrir el archivo de log\n");
            exit(1);
        }

        // Posicionar el puntero en la última posición leída
        fseek(fp, last_position, SEEK_SET);

        // Leer cada línea del archivo
        while (fgets(line, sizeof(line), fp)) {
            // Verificar si la línea es completa (termina con un salto de línea)
            if (line[strlen(line) - 1] != '\n') {
                // No procesamos líneas incompletas
                continue;
            }

            // Guardar la posición actual del puntero en el archivo
            last_position = ftell(fp);

            // Analizar la línea para obtener los datos
            sscanf(line, "Timestamp: %s, PID: %d, Process: %s, Syscall: %s, Size: %d",
                   timestamp, &pid, process, syscall_name, &size);

            // Insertar en la base de datos
            if (insert_log_to_mysql(conn, timestamp, pid, process, syscall_name, size) != 0) {
                fprintf(stderr, "Error al insertar en MySQL\n");
            }
        }

        fclose(fp);

        // Esperar 2 segundos antes de volver a abrir el archivo
        sleep(2);
    }

    mysql_close(conn);
    return 0;
}
