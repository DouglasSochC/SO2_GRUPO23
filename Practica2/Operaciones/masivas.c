#include "masivas.h"
#include <cjson/cJSON.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void cargarUsuarios(int *cantidadUsuarios, Usuario *usuarios)
{

    char rutaArchivo[] = "Carga/usuarios.json";
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
    usuarios = (Usuario *)malloc(cantidad * sizeof(Usuario));
    *cantidadUsuarios = cantidad;

    for (int i = 0; i < cantidad; i++)
    {
        cJSON *item = cJSON_GetArrayItem(json, i);
        usuarios[i].no_cuenta = cJSON_GetObjectItem(item, "no_cuenta")->valueint;
        strcpy(usuarios[i].nombre, cJSON_GetObjectItem(item, "nombre")->valuestring);
        usuarios[i].saldo = cJSON_GetObjectItem(item, "saldo")->valuedouble;
    }

    printf("\nCarga masiva de usuarios realizada desde %s.\n", rutaArchivo);

    // Limpiar memoria
    cJSON_Delete(json);
    free(fileContent);
}

void cargarOperaciones(int *cantidadOperaciones, Operacion *operaciones)
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