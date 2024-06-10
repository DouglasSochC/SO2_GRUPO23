# Llamadas de Sistema

_Este es una practica universitaria del curso de Sistemas Operativos 2, en el cual consiste en escribir un programa que sea capaz de monitorear y almacenar en un log todas las llamadas de sistema realizadas por procesos hijos que se cree_

## 🚀 Comenzando

### 📋 Requerimientos

* Desarrollado en Linux mint
* Lenguaje de programacion C 
* Codigo de respaldo con systemtap
* GCC 11.4.0

    ```console
    gcc --version
    ```
*   make (última versión)
    
    ```console
    make --version
    ``` 

####    Instalacion de herramientas

-   apt update && apt upgrade
-   sudo apt install systemtap
-   sudo apt install gcc
-   sudo apt install make

### ⚙️ Ejecucion

Para ejecutar el programa, únicamente ejecutamos el comando make, dado que estamos utilizando un makefile para la compilación de ambos archivos (parent.h y child.c) y hemos designado ese comando, luego en el mismo archivo, generamos los ejecutables (parent y child.bin) y procedemos con la ejecución del archivo parent.

En cualquier momento duranta la ejecución del programa, podemos presionar la combinación de teclas ctrl + c y por medio de esta señal de SIGINT, al detectarla, se para el programa y nos muestra un resumen de las syscalls realizadas por los procesos hijos creados, los cuales se encuntran aleatoreamente generando llamadas de lectura o escritura sobre el archivo practica1.txt y almacenando un histórico de las syscalls en un archivo syscalls.log, archivo generado por el proceso padre y escrito por las instrucciones de systemtap en el archivo trace.stp 

![Ejecucion del sistema](./imagenes/ejecucion.png)
![Logs del sistema](./imagenes/syscallslog.png)
