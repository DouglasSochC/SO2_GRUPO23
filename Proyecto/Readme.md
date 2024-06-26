# Manejo de memoria

_Este es un proyecto universitario del curso de Sistemas Operativos 2, en el cual se creara una aplicación capaz de monitorear el uso de memoria de cada proceso abierto en Linux, detectando las solicitudes de memoria que estos realizan al sistema operativo._

## 🚀 Comenzando

### 📋 Requerimientos

* [GCC 11.4.0](https://phoenixnap.com/kb/install-gcc-ubuntu)
```console
gcc --version
```

#### Adicionales

* Libreria del cliente MySQL para C

```console
sudo apt update
sudo apt install libmysqlclient-dev
```

### ⚙️ Ejecucion

#### Generador

Para ejecutar el generador, primero es necesario definir su archivo .env. Una vez creado el archivo .env, ejecute los siguientes comandos.

* Cargar las variables de entorno

    ```console
    source .env
    ```

* Compilar y ejecutar el generador

    ```console
    make all
    ```

## 📖 Documentacion

# Documentación del Sistema de Monitoreo de Memoria

## Índice

1. [Introducción](#introducción)
2. [Arquitectura del Sistema](#arquitectura-del-sistema)
3. [Instalación y Configuración](#instalación-y-configuración)
   - [Prerrequisitos](#prerrequisitos)
   - [Configuración de Docker](#configuración-de-docker)
   - [Configuración de la Base de Datos](#configuración-de-la-base-de-datos)
   - [Construcción y Ejecución del Sistema](#construcción-y-ejecución-del-sistema)
4. [Descripción de los Componentes](#descripción-de-los-componentes)
   - [Backend](#backend)
   - [Frontend](#frontend)
   - [Sistema de Monitoreo](#sistema-de-monitoreo)
5. [Detalles del Código](#detalles-del-código)
   - [Archivos C](#archivos-c)
   - [Scripts SystemTap](#scripts-systemtap)
   - [Archivos SQL](#archivos-sql)
   - [Makefile](#makefile)
   - [Docker Compose](#docker-compose)
   - [Backend (Node.js)](#backend-nodejs)
   - [Frontend (React)](#frontend-react)
6. [Uso del Sistema](#uso-del-sistema)
7. [Consideraciones de Seguridad](#consideraciones-de-seguridad)
8. [Solución de Problemas](#solución-de-problemas)

## Introducción

Este proyecto es un sistema de monitoreo de memoria que rastrea el uso de memoria en procesos a través de `SystemTap` y almacena la información en una base de datos MySQL. El sistema cuenta con un backend desarrollado en Node.js y un frontend en React para visualizar la información de los procesos.

## Arquitectura del Sistema

La arquitectura del sistema se compone de tres partes principales:

1. **Backend:** Implementado en Node.js, maneja las conexiones a la base de datos y expone una API para interactuar con el frontend.
2. **Frontend:** Desarrollado en React, proporciona una interfaz de usuario para visualizar el uso de memoria de los procesos.
3. **Sistema de Monitoreo:** Utiliza `SystemTap` para rastrear las llamadas al sistema relacionadas con la memoria (`mmap2` y `munmap`) y almacenar los datos en una base de datos MySQL.

## Instalación y Configuración

### Prerrequisitos

Asegúrate de tener los siguientes componentes instalados en tu sistema:

- Docker y Docker Compose
- SystemTap
- MySQL Client Libraries (libmysqlclient-dev en sistemas Debian/Ubuntu)
- GCC (GNU Compiler Collection)

### Configuración de Docker

El sistema utiliza Docker para la contenedorización de los servicios. A continuación, se describe cómo configurar Docker para este proyecto.

#### Docker Compose

El archivo `docker-compose.yml` define los servicios Docker necesarios para ejecutar el sistema. Incluye la configuración para tres servicios principales:

- **Database:** Un contenedor que utiliza la imagen de una base de datos MySQL personalizada, configurada para almacenar los datos del monitoreo.
- **Backend:** Un contenedor que ejecuta el backend desarrollado en Node.js, que maneja las conexiones a la base de datos y sirve la API REST.
- **Frontend:** Un contenedor que ejecuta la aplicación de React, que se comunica con el backend para mostrar los datos de monitoreo al usuario.

### Configuración de la Base de Datos

El archivo `db_init.sql` crea la base de datos y la tabla necesarias para almacenar los datos de los procesos. Especifica las instrucciones SQL para:

- Crear una base de datos llamada `proceso_db`.
- Crear una tabla llamada `procesos` con campos para almacenar información como el ID del proceso, el nombre del proceso, la llamada de sistema realizada, el tamaño del segmento de memoria y la fecha y hora de la solicitud.

### Construcción y Ejecución del Sistema

Para construir y ejecutar el sistema, sigue estos pasos:

1. **Clonar el repositorio:** Descarga el código fuente del proyecto.
2. **Navegar a la carpeta del proyecto:** Utiliza la terminal para moverte al directorio donde se encuentra el proyecto.
3. **Construir los servicios Docker:** Usa Docker Compose para construir las imágenes de los servicios definidos en el archivo `docker-compose.yml`.
4. **Iniciar los servicios Docker:** Usa Docker Compose para iniciar los contenedores. Esto arrancará los contenedores de la base de datos, el backend y el frontend.

## Descripción de los Componentes

### Backend

El backend está implementado en Node.js y se encarga de manejar las conexiones a la base de datos y proporcionar una API para el frontend. A continuación, se describen los archivos y sus funcionalidades:

- **`index.js`:** Es el punto de entrada del servidor backend. Configura el servidor Express, define el puerto en el que el servidor escuchará y configura el uso del enrutador para manejar las peticiones API.
- **`router.js`:** Define las rutas del API del backend y sus controladores correspondientes. Incluye endpoints para:
  - Verificar la conexión con la base de datos.
  - Obtener los últimos 50 registros de la tabla de procesos.
  - Obtener el top 10 de procesos con más memoria utilizada.

### Frontend

El frontend está desarrollado en React y proporciona una interfaz de usuario para visualizar el uso de memoria de los procesos. A continuación, se describen los archivos y componentes clave:

- **`App.js`:** Es el punto de entrada de la aplicación React. Maneja la visualización de los datos obtenidos del backend, como los registros de procesos monitoreados.
- **Componentes de UI:** Se encarga de mostrar la información en un formato amigable para el usuario, como tablas y gráficos.

### Sistema de Monitoreo

El sistema de monitoreo utiliza `SystemTap` para rastrear las llamadas al sistema `mmap2` y `munmap`. A continuación, se describen los scripts y su funcionalidad:

- **`memory_trace.stp`:** Es un script de `SystemTap` que rastrea las llamadas al sistema `mmap2` y `munmap`. Captura detalles como el ID del proceso, la dirección de memoria y el tamaño del segmento, y los registra para su posterior procesamiento.

## Detalles del Código

### Archivos C

Estos archivos implementan la lógica para ejecutar y procesar la salida del script de `SystemTap`.

- **`main.c`:** Es el punto de entrada del programa en C. Su función principal es ejecutar el script `SystemTap`.
- **`reader.c`:** Define las funciones para ejecutar el script `SystemTap` y procesar su salida. Incluye:
  - Función para ejecutar el script `SystemTap` y capturar su salida.
  - Función para procesar la información obtenida del script.

### Scripts SystemTap

El sistema utiliza scripts `SystemTap` para rastrear las llamadas al sistema relacionadas con la memoria.

- **`memory_trace.stp`:** Este script rastrea las llamadas `mmap2` y `munmap`. Imprime detalles sobre cada llamada, incluyendo el ID del proceso, la dirección de memoria y el tamaño del segmento.

### Archivos SQL

Estos archivos inicializan la base de datos y crean la estructura necesaria para almacenar los datos del monitoreo.

- **`db_init.sql`:** Este archivo SQL crea la base de datos y la tabla necesarias para almacenar los datos de los procesos. Incluye instrucciones para crear la base de datos `proceso_db` y la tabla `procesos`.

### Makefile

El `Makefile` proporciona instrucciones para compilar y ejecutar el programa en C. Define reglas para:

- Compilar los archivos `.c` en archivos objeto `.o`.
- Enlazar los archivos objeto para crear el ejecutable final.
- Limpiar los archivos generados durante la compilación.

### Docker Compose

El archivo `docker-compose.yml` define y configura los servicios Docker necesarios para ejecutar el sistema. Especifica cómo construir las imágenes de Docker y cómo configurar los contenedores para la base de datos, el backend y el frontend.

### Backend (Node.js)

El backend está implementado en Node.js y maneja la lógica del servidor y las conexiones a la base de datos. Incluye archivos y funciones para:

- **`index.js`:** Configura el servidor Express y define el puerto en el que escuchará.
- **`router.js`:** Define las rutas del API y los controladores para manejar las peticiones de los clientes. Las rutas incluyen:
  - `/hello`: Verifica la conexión con la base de datos.
  - `/procesos`: Obtiene los últimos 50 registros de la tabla de procesos.
  - `/memory`: Obtiene el top 10 de procesos con más memoria utilizada.

### Frontend (React)

El frontend está desarrollado en React y proporciona una interfaz para que los usuarios visualicen los datos del monitoreo. Incluye:

- **`App.js`:** Es el componente principal de la aplicación React. Maneja la visualización de los datos obtenidos del backend y organiza la estructura de la aplicación.
- **Componentes de UI:** Se encargan de mostrar los datos de manera clara y organizada, como tablas y gráficos interactivos.

## Uso del Sistema

Para usar el sistema, sigue estos pasos:

1. **Inicia el sistema:** Usa Docker Compose para levantar los contenedores.
2. **Accede al frontend:** Abre un navegador web y dirígete a la URL del frontend (por defecto, http://localhost).
3. **Monitorea los procesos:** La interfaz mostrará los datos de uso de memoria de los procesos en tiempo real, obtenidos del backend.

## Consideraciones de Seguridad

Para asegurar el sistema, considera los siguientes aspectos:

- **Configuración de la base de datos:** Asegúrate de que las credenciales de la base de datos están protegidas y no se exponen públicamente.
- **Comunicación segura:** Implementa HTTPS para asegurar la comunicación entre el frontend y el backend.
- **Restricciones de acceso:** Configura reglas de firewall y políticas de seguridad para limitar el acceso a los contenedores y la base de datos.

## Solución de Problemas

Aquí hay algunos consejos para solucionar problemas comunes:

- **Problemas de conexión a la base de datos:** Verifica que las credenciales y la configuración de la base de datos en el archivo `docker-compose.yml` son correctas.
- **Errores en la compilación del código C:** Asegúrate de que todas las dependencias necesarias están instaladas y configuradas correctamente.
- **Problemas con Docker:** Verifica que Docker y Docker Compose están instalados y configurados correctamente. Usa `docker-compose logs` para ver los registros de los contenedores y diagnosticar problemas.


