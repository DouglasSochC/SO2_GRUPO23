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