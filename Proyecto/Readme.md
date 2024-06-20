#   Para compilar Systemtap

Usar el comando: sudo stap -v -DDEBUG memory_tracer.stp

#   Para instalar la libreria del cliente de Mysql 

Usar los comandos:

-   sudo apt update
-   sudo apt install libmysqlclient-dev

#   Para compilar el archivo reader.c

Usar el comando: gcc -o reader reader.c -lmysqlclient

