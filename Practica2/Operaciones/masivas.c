#include "masivas.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdbool.h>

extern Usuario *usuarios;
extern int cantidadUsuarios;
extern Error *errores;
pthread_mutex_t lock;
char nombreArchivoUsuarios[100];

void cargaMasivaUsuarios()
{
    // Se crea el archivo log para ir almacenando la informacion que se obtuvo durante la carga de usuarios
    crearArchivoLogUsuarios();

    pthread_mutex_init(&lock, NULL); // Inicializamos nuestro mutex
    pthread_t hilos[3];
    int ids[3] = {0, 1, 2};

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&hilos[i], NULL, lecturaArchivoUsuarios, &ids[i]);
    }

    int cantidades[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++)
    {
        void *ret_val;
        pthread_join(hilos[i], &ret_val);
        cantidades[i] = *(int *)ret_val;
    }
    pthread_mutex_destroy(&lock); // Liberamos los recursos del semaforo

    escribirEnArchivo(nombreArchivoUsuarios, "Usuarios Cargados:");
    int totalTemp = 0;
    char textoTemp[100];
    for (int i = 0; i < 3; i++)
    {
        totalTemp += cantidades[i];
        sprintf(textoTemp, "Hilo #%d: %d", i + 1, cantidades[i]);
        escribirEnArchivo(nombreArchivoUsuarios, textoTemp);
        memset(textoTemp, '\0', sizeof(textoTemp)); // Se limpia la variable
    }

    sprintf(textoTemp, "Total : %d", totalTemp);
    escribirEnArchivo(nombreArchivoUsuarios, textoTemp);
    escribirEnArchivo(nombreArchivoUsuarios, "");
    escribirEnArchivo(nombreArchivoUsuarios, "Errores:");
    memset(textoTemp, '\0', sizeof(textoTemp)); // Se limpia la variable

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (strcmp(errores[i].descripcion, "") != 0)
        {
            escribirEnArchivo(nombreArchivoUsuarios, errores[i].descripcion);
        }
    }
}

void *lecturaArchivoUsuarios(void *arg)
{
    // Variable para identificar la cantidad de datos que leo el hilo
    int *cantidadDatosLeidos = malloc(sizeof(int));
    *cantidadDatosLeidos = 0;
    // Obtencion del id del hilo
    int hilo_id = *((int *)arg);

    char rutaArchivo[] = "Carga/usuarios.json";
    FILE *file = fopen(rutaArchivo, "r");
    if (file == NULL)
    {
        printf("\nNo se puede abrir el archivo %s.\n", rutaArchivo);
    }

    // Obtener el tamaño del archivo
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Leer el archivo en una cadena
    char *fileContent = (char *)malloc(fileSize + 1);
    fread(fileContent, 1, fileSize, file);
    fclose(file);
    fileContent[fileSize] = '\0';

    // Parsear el JSON
    cJSON *json = cJSON_Parse(fileContent);
    if (json == NULL)
    {
        printf("\nError al parsear el archivo JSON.\n");
        free(fileContent);
    }

    int cantidad = cJSON_GetArraySize(json);
    pthread_mutex_lock(&lock);
    if (usuarios == NULL)
    {
        usuarios = (Usuario *)malloc(cantidad * sizeof(Usuario));
        errores = (Error *)malloc(cantidad * sizeof(Error));
    }
    pthread_mutex_unlock(&lock);

    int tamanio_bloque = cantidad / 3;
    int indice_inicio = hilo_id * tamanio_bloque;
    int indice_final = (hilo_id == 2) ? cantidad : (hilo_id + 1) * tamanio_bloque;

    for (int i = indice_inicio; i < indice_final; i++)
    {
        cantidadUsuarios++;
        pthread_mutex_lock(&lock);
        cJSON *item = cJSON_GetArrayItem(json, i);
        // printf("Hilo %d: Cargando usuario %d\n", hilo_id, cJSON_GetObjectItem(item, "no_cuenta")->valueint);
        cJSON *no_cuenta = cJSON_GetObjectItem(item, "no_cuenta");
        cJSON *nombre = cJSON_GetObjectItem(item, "nombre");
        cJSON *saldo = cJSON_GetObjectItem(item, "saldo");
        validarUsuario(i, no_cuenta, nombre, saldo);
        (*cantidadDatosLeidos)++;
        pthread_mutex_unlock(&lock);
    }
    printf("\nCarga masiva de usuarios realizada desde %s y el hilo con ID %d.\n", rutaArchivo, hilo_id);
    // Limpiar memoria
    cJSON_Delete(json);
    free(fileContent);

    // Devolver la cantidad de datos que leyo el hilo
    pthread_exit(cantidadDatosLeidos);
}

void cargarOperaciones(Operacion *operaciones, int *cantidadOperaciones)
{

    char rutaArchivo[] = "Carga/operaciones.json";
    FILE *file = fopen(rutaArchivo, "r");
    if (file == NULL)
    {
        printf("\nNo se puede abrir el archivo %s.\n", rutaArchivo);
        return;
    }

    // Obtener el tamaño del archivo
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Leer el archivo en una cadena
    char *fileContent = (char *)malloc(fileSize + 1);
    fread(fileContent, 1, fileSize, file);
    fclose(file);
    fileContent[fileSize] = '\0';

    // Parsear el JSON
    cJSON *json = cJSON_Parse(fileContent);
    if (json == NULL)
    {
        printf("\nError al parsear el archivo JSON.\n");
        free(fileContent);
        return;
    }

    int cantidad = cJSON_GetArraySize(json);
    operaciones = (Operacion *)malloc(cantidad * sizeof(Operacion));
    *cantidadOperaciones = cantidad;

    for (int i = 0; i < cantidad; i++)
    {
        cJSON *item = cJSON_GetArrayItem(json, i);
        operaciones[i].operacion = cJSON_GetObjectItem(item, "operacion")->valueint;
        operaciones[i].cuenta1 = cJSON_GetObjectItem(item, "cuenta1")->valueint;
        operaciones[i].cuenta2 = cJSON_GetObjectItem(item, "cuenta2")->valueint;
        operaciones[i].monto = cJSON_GetObjectItem(item, "monto")->valuedouble;
    }

    printf("\nCarga masiva de operaciones realizada desde %s.\n", rutaArchivo);

    // Limpiar memoria
    cJSON_Delete(json);
    free(fileContent);
}

void crearArchivoLogUsuarios()
{
    // Obtener la hora actual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Crear una cadena para almacenar la fecha y hora formateada
    char fechaHora[20];
    char textoFechaHora[20];

    // Formatear la fecha y hora
    snprintf(fechaHora, sizeof(fechaHora), "%04d_%02d_%02d-%02d_%02d_%02d",
             tm.tm_year + 1900, // Año
             tm.tm_mon + 1,     // Mes (0-11, por eso se suma 1)
             tm.tm_mday,        // Día del mes
             tm.tm_hour,        // Hora
             tm.tm_min,         // Minuto
             tm.tm_sec);        // Segundo

    // Formatear la fecha y hora
    snprintf(textoFechaHora, sizeof(textoFechaHora), "%04d-%02d-%02d %02d:%02d:%02d",
             tm.tm_year + 1900, // Año
             tm.tm_mon + 1,     // Mes (0-11, por eso se suma 1)
             tm.tm_mday,        // Día del mes
             tm.tm_hour,        // Hora
             tm.tm_min,         // Minuto
             tm.tm_sec);        // Segundo

    // Se crea la carpeta
    mkdir("Reportes", 0777);
    // Se formatea el nombre del archivo
    sprintf(nombreArchivoUsuarios, "Reportes/carga_%s.log", fechaHora);

    // Abrir el archivo en modo escritura, lo creará si no existe.
    FILE *file = fopen(nombreArchivoUsuarios, "a");

    // Se escribe el titulo
    fprintf(file, "%s\n", "----------------- Carga de Usuarios -----------------\n");

    // Se escribe la fecha
    fprintf(file, "%s", "Fecha: ");
    fprintf(file, "%s", textoFechaHora);
    fprintf(file, "%s", "\n\n");

    // Cerrar el archivo
    fclose(file);
}

void escribirEnArchivo(char *nombreArchivo, char *texto)
{
    FILE *archivo = fopen(nombreArchivo, "a"); // Abre el archivo en modo append
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    fprintf(archivo, "%s\n", texto); // Escribe la línea de texto en el archivo
    fclose(archivo);                 // Cierra el archivo
}

void validarUsuario(int fila, cJSON *numCuenta, cJSON *nombre, cJSON *saldo)
{
    bool exito = true;

    // Se verifica si el numero de cuenta es entero
    if (numCuenta != NULL && cJSON_IsNumber(numCuenta))
    {
        // Se verifica si el numero de cuenta ya existe
        for (int i = 0; i < cantidadUsuarios; i++)
        {
            if (usuarios[i].no_cuenta == numCuenta->valueint)
            {
                sprintf(errores[fila].descripcion, "  - Estructura #%d: Numero de cuenta duplicada.", (fila + 1));
                exito = false;
                break;
            }
        }
    }
    else
    {
        sprintf(errores[fila].descripcion, "  - Estructura #%d: Numero de cuenta no valida.", (fila + 1));
        exito = false;
    }

    // Se verifica que el nombre sea texto
    if (!(nombre != NULL && cJSON_IsString(nombre)))
    {
        sprintf(errores[fila].descripcion, "  - Estructura #%d: Nombre no valido.", (fila + 1));
        exito = false;
    }

    // Se verifica si el saldo es double
    if (saldo != NULL && cJSON_IsNumber(saldo))
    {
        if (saldo->valuedouble < 0)
        {
            sprintf(errores[fila].descripcion, "  - Estructura #%d: El saldo no puede ser menor a 0.", (fila + 1));
            exito = false;
        }
    }
    else
    {
        sprintf(errores[fila].descripcion, "  - Estructura #%d: Saldo no valido.", (fila + 1));
        exito = false;
    }

    // En el dado caso que todo este bien se registra el usuario
    if (exito)
    {
        usuarios[fila].no_cuenta = numCuenta->valueint;
        strcpy(usuarios[fila].nombre, nombre->valuestring);
        usuarios[fila].saldo = saldo->valuedouble;
    }
    else
    {
        usuarios[fila].no_cuenta = -1;
    }
}