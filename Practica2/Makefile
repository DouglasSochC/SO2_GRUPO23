# Define los compiladores y las opciones de compilación
CC = gcc
CFLAGS = -lcjson -lm -Wno-unused-result

# Nombres de los archivos de salida
MAIN_BIN = main

# Objetivos (targets)
all: clean $(MAIN_BIN) run

# Regla para compilar main.c en main
$(MAIN_BIN):
	$(CC) -o $(MAIN_BIN) main.c cJSON/cJSON.c Operaciones/individuales.c Operaciones/masivas.c Operaciones/reportes.c $(CFLAGS)

# Regla para ejecutar el programa parent
run:
	./$(MAIN_BIN)

# Limpiar los archivos generados
clean:
	rm -f $(MAIN_BIN)

.PHONY: all clean run
