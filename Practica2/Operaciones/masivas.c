#include "masivas.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pthread.h>

extern Usuario *usuarios;
extern int cantidadUsuarios;
extern Error *errores;
extern int cantidadErrores;
pthread_mutex_t lock;
char nombreArchivoUsuarios[100];
char nombreArchivoOperaciones[100];

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

    if (errores != NULL)
    {
        for (int i = 0; i < cantidadErrores; i++)
        {
            if (strcmp(errores[i].descripcion, "") != 0)
            {
                escribirEnArchivo(nombreArchivoUsuarios, errores[i].descripcion);
            }
        }
        errores = NULL;
    }
}

void cargaMasivaOperaciones()
{
    // Se crea el archivo log para ir almacenando la informacion que se obtuvo durante la carga de las operaciones
    crearArchivoLogOperaciones();

    pthread_mutex_init(&lock, NULL); // Inicializamos nuestro mutex
    pthread_t hilos[4];
    int ids[4] = {0, 1, 2, 3};

    for (int i = 0; i < 4; i++)
    {
        pthread_create(&hilos[i], NULL, lecturaArchivoOperaciones, &ids[i]);
    }

    int cantidades[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        void *ret_val;
        pthread_join(hilos[i], &ret_val);
        cantidades[i] = *(int *)ret_val;
    }
    pthread_mutex_destroy(&lock); // Liberamos los recursos del semaforo

    escribirEnArchivo(nombreArchivoOperaciones, "Operaciones por hilo:");
    int totalHilosTemp = 0;
    char textoTemp[100];
    for (int i = 0; i < 4; i++)
    {
        totalHilosTemp += cantidades[i];
        sprintf(textoTemp, "Hilo #%d: %d", i + 1, cantidades[i]);
        escribirEnArchivo(nombreArchivoOperaciones, textoTemp);
        memset(textoTemp, '\0', sizeof(textoTemp)); // Se limpia la variable
    }

    sprintf(textoTemp, "Total : %d", totalHilosTemp);
    escribirEnArchivo(nombreArchivoOperaciones, textoTemp);
    escribirEnArchivo(nombreArchivoOperaciones, "");
    escribirEnArchivo(nombreArchivoOperaciones, "Errores:");
    memset(textoTemp, '\0', sizeof(textoTemp)); // Se limpia la variable

    if (errores != NULL)
    {
        for (int i = 0; i < cantidadErrores; i++)
        {
            if (strcmp(errores[i].descripcion, "") != 0)
            {
                escribirEnArchivo(nombreArchivoOperaciones, errores[i].descripcion);
            }
        }
        errores = NULL;
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
        int *retval = malloc(sizeof(int));
        *retval = -1;
        pthread_exit(retval);
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
        int *retval = malloc(sizeof(int));
        *retval = -1;
        pthread_exit(retval);
    }

    int cantidad = cJSON_GetArraySize(json);
    pthread_mutex_lock(&lock);
    if (usuarios == NULL)
    {
        usuarios = (Usuario *)malloc(cantidad * sizeof(Usuario));
    }
    if (errores == NULL)
    {
        errores = (Error *)malloc(cantidad * sizeof(Error));
        cantidadErrores = cantidad;
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

    // Limpiar memoria
    cJSON_Delete(json);
    free(fileContent);

    // Devolver la cantidad de datos que leyo el hilo
    pthread_exit(cantidadDatosLeidos);
}

void *lecturaArchivoOperaciones(void *arg)
{
    // Variable para identificar la cantidad de datos que leo el hilo
    int *cantidadDatosLeidos = malloc(sizeof(int));
    *cantidadDatosLeidos = 0;

    // Obtencion del id del hilo
    int hilo_id = *((int *)arg);

    // Manejo del archivo
    char rutaArchivo[] = "Carga/operaciones.json";
    FILE *file = fopen(rutaArchivo, "r");
    if (file == NULL)
    {
        printf("\nNo se puede abrir el archivo %s.\n", rutaArchivo);
        int *retval = malloc(sizeof(int));
        *retval = -1;
        pthread_exit(retval);
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
        int *retval = malloc(sizeof(int));
        *retval = -1;
        pthread_exit(retval);
    }

    int cantidad = cJSON_GetArraySize(json);
    pthread_mutex_lock(&lock);
    if (errores == NULL)
    {
        errores = (Error *)malloc(cantidad * sizeof(Error));
        cantidadErrores = cantidad;
    }
    pthread_mutex_unlock(&lock);
    int tamanio_bloque = cantidad / 4;
    int indice_inicio = hilo_id * tamanio_bloque;
    int indice_final = (hilo_id == 3) ? cantidad : (hilo_id + 1) * tamanio_bloque;

    for (int i = indice_inicio; i < indice_final; i++)
    {
        pthread_mutex_lock(&lock);
        (*cantidadDatosLeidos)++;
        cJSON *item = cJSON_GetArrayItem(json, i);
        cJSON *operacion = cJSON_GetObjectItem(item, "operacion");
        cJSON *cuenta1 = cJSON_GetObjectItem(item, "cuenta1");
        cJSON *cuenta2 = cJSON_GetObjectItem(item, "cuenta2");
        cJSON *monto = cJSON_GetObjectItem(item, "monto");
        bool respuesta = validarOperacion(i, operacion, cuenta1, cuenta2, monto);
        if (respuesta)
        {
            int operacion = cJSON_GetObjectItem(item, "operacion")->valueint;
            int aux_cuenta_1 = cJSON_GetObjectItem(item, "cuenta1")->valueint;
            int aux_cuenta_2 = cJSON_GetObjectItem(item, "cuenta2")->valueint;
            double monto = cJSON_GetObjectItem(item, "monto")->valuedouble;
            int res_operacion = 0;

            if (operacion == 1)
            {
                res_operacion = deposito(aux_cuenta_1, monto);
            }
            else if (operacion == 2)
            {
                res_operacion = retiro(aux_cuenta_1, monto);
            }
            else if (operacion == 3)
            {
                res_operacion = transaccion(aux_cuenta_1, aux_cuenta_2, monto);
            }
            if (res_operacion != 0)
            {
                char *resMensajeOperacion = obtenerMensajeOperacion(res_operacion);
                sprintf(errores[i].descripcion, "  - Estructura #%d: %s", (i + 1), resMensajeOperacion);
            }
        }
        pthread_mutex_unlock(&lock);
    }

    // Limpiar memoria
    cJSON_Delete(json);
    free(fileContent);

    // Devolver la cantidad de datos que leyo el hilo
    pthread_exit(cantidadDatosLeidos);
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

void crearArchivoLogOperaciones()
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
    sprintf(nombreArchivoOperaciones, "Reportes/operaciones_%s.log", fechaHora);

    // Abrir el archivo en modo escritura, lo creará si no existe.
    FILE *file = fopen(nombreArchivoOperaciones, "a");

    // Se escribe el titulo
    fprintf(file, "%s\n", "----------------- Operaciones Realizadas -----------------\n");

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
        if (numCuenta == 0)
        {
            sprintf(errores[fila].descripcion, "  - Estructura #%d: Numero de cuenta no valida.", (fila + 1));
            exito = false;
        }
        else
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

bool validarOperacion(int fila, cJSON *operacion, cJSON *numCuentaOrigen, cJSON *numCuentaDestino, cJSON *monto)
{
    bool exito = true;

    // Se verifica que la operacion sea entera
    if (operacion != NULL && cJSON_IsNumber(operacion))
    {
        // Se verifica que el tipo de operacion sea 1, 2 o 3
        if (!(operacion->valueint == 1 || operacion->valueint == 2 || operacion->valueint == 3))
        {
            sprintf(errores[fila].descripcion, "  - Estructura #%d: Código de operación desconocido.", (fila + 1));
            exito = false;
        }
    }
    else
    {
        sprintf(errores[fila].descripcion, "  - Estructura #%d: La operación no es válida.", (fila + 1));
        exito = false;
    }

    // Se verifica si el numero de cuenta de origen es entero
    if (!(numCuentaOrigen != NULL && cJSON_IsNumber(numCuentaOrigen)))
    {
        sprintf(errores[fila].descripcion, "  - Estructura #%d: Numero de cuenta 1 no valida.", (fila + 1));
        exito = false;
    }

    // Se verifica si el numero de cuenta de destino es entero
    if (!(numCuentaDestino != NULL && cJSON_IsNumber(numCuentaDestino)))
    {
        sprintf(errores[fila].descripcion, "  - Estructura #%d: Numero de cuenta 2 no valida.", (fila + 1));
        exito = false;
    }

    // Se verifica si el monto es double
    if (!(monto != NULL && cJSON_IsNumber(monto)))
    {
        sprintf(errores[fila].descripcion, "  - Estructura #%d: El monto ingresado no es un número válido.", (fila + 1));
        exito = false;
    }

    return exito;
}