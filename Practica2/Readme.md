# Documentación del Proyecto

Este Readme proporciona una visión general del proyecto y documenta las funcionalidades del software desarrollado, así como el proceso de desarrollo de los diferentes módulos.

## Descripción del Proyecto

El proyecto consiste en un sistema de gestión bancaria que permite cargar usuarios de manera masiva desde archivos JSON, realizar operaciones individuales como depósitos, retiros y transferencias entre cuentas, generar reportes del estado de cuentas en formato JSON, y gestionar errores asociados a las operaciones y la carga de usuarios.

## Estructura del Proyecto

El proyecto está estructurado en varios archivos y carpetas:

- **main.c**: Contiene la función principal (`main`) y el menú principal del programa.
- **masivas.c**: Implementa la carga masiva de usuarios desde archivos JSON.
- **individuales.c**: Implementa las operaciones individuales como depósitos, retiros, transferencias y consultas de cuentas.
- **reportes.c**: Implementa la generación de reportes del estado de cuentas en formato JSON.
- **Operaciones/**: Carpeta que contiene los archivos de cabecera y fuente para operaciones masivas e individuales.
- **Estructuras/**: Carpeta que contiene los archivos de cabecera para las estructuras de datos utilizadas.
- **cJSON/**: Carpeta que contiene la biblioteca cJSON para el manejo de JSON en C.
- **constantes.h**: Define las constantes utilizadas para los códigos de retorno de las operaciones.
- **operacion.h**: Define la estructura de datos `Operacion`.
- **usuario.h**: Define la estructura de datos `Usuario`.

## Funcionalidades del Software

### Carga Masiva de Usuarios

La carga masiva de usuarios se realiza desde archivos JSON ubicados en la carpeta `Carga`. Se utilizan hilos para leer y validar los datos de los usuarios en paralelo, almacenando los usuarios válidos en un arreglo dinámico. Se genera un archivo de log (`carga_fechaHora.log`) que registra los usuarios cargados y los errores encontrados durante la carga.

### Operaciones Individuales

Las operaciones individuales permiten realizar las siguientes acciones:

- **Depósito**: Incrementa el saldo de una cuenta específica.
- **Retiro**: Decrementa el saldo de una cuenta específica si el saldo es suficiente.
- **Transferencia**: Transfiere un monto de una cuenta de origen a una cuenta de destino, validando que ambas cuentas existan y que la cuenta de origen tenga saldo suficiente.
- **Consulta de Cuenta**: Muestra información detallada (número de cuenta, nombre y saldo) de una cuenta específica.

### Generación de Reportes

Se genera un reporte del estado de cuentas en formato JSON (`Reporte_Estados_Cuentas.json`). El reporte incluye información detallada de todos los usuarios cargados correctamente, omitiendo aquellos usuarios con datos inválidos.

### Gestión de Errores

Durante la carga masiva de usuarios y la ejecución de operaciones individuales, se manejan errores como números de cuenta duplicados, nombres no válidos, saldos no válidos, entre otros. Los errores se registran en el archivo de log correspondiente (`carga_fechaHora.log`).

## Desarrollo de los Módulos

### Carga Masiva de Usuarios (`masivas.c`)

- **Funciones Principales**:
  - `cargaMasivaUsuarios()`: Función principal que inicia la carga masiva de usuarios desde el archivo JSON.
  - `lecturaArchivoUsuarios(void *arg)`: Función ejecutada por hilos para leer y validar datos de usuarios.
  - `crearArchivoLogUsuarios()`: Crea el archivo de log con la fecha y hora de la carga.

### Operaciones Individuales (`individuales.c`)

- **Funciones Principales**:
  - `menuOperacionIndividual(Usuario *usuarios, int cantidadUsuarios)`: Muestra un menú para realizar operaciones individuales.
  - Funciones específicas como `deposito`, `retiro`, `transaccion`, `consultarCuenta` para cada operación individual.
  - `imprimirMensajeOperacion(int codigo)`: Imprime mensajes correspondientes a los códigos de retorno de las operaciones.

### Generación de Reportes (`reportes.c`)

- **Funciones Principales**:
  - `generarReporteCuentas(Usuario *usuarios, int cantidadUsuarios)`: Genera un reporte del estado de cuentas en formato JSON.

## Constantes Utilizadas (`constantes.h`)

Define las constantes utilizadas para los códigos de retorno de las operaciones:
- `EXITO`, `CUENTA_INEXISTENTE`, `MONTO_NO_ES_NUMERO`, `MONTO_ES_MENOR_A_0`, `SALDO_INSUFICIENTE`, `OPERACION_NO_VALIDA`.



##  Para instalar cMake:
*   sudo apt install cmake
*   sudo apt-get install libcjson-dev (sistemas basados en Debian)


## Para instalar la libreria cJSON:
*   Clonar el repositorio https://github.com/DaveGamble/cJSON.git
*   ejecutar los comandos:
    -   mkdir build
    -   cd build
    -   cmake ..
    -   make
    -   make install
*   Opcion 2:
    -   mkdir build
    -   cd build
    -   cmake .. -DENABLE_CJSON_UTILS=On -DENABLE_CJSON_TEST=Off -DCMAKE_INSTALL_PREFIX=/usr
    -   make
    -   make DESTDIR=$pkgdir install

## Para compilar y ejecutar el proyecto
* make all

##  Para compilar usando la libreria cJSON:
*   gcc -o main main.c cJSON.c -lcjson -lm
*   No olvidar agregar los archivos cJSON.c Y cJSON.h al directorio del proyecto