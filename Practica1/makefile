# Define los compiladores y las opciones de compilación
CC = gcc
CFLAGS = -Wall -O2

# Nombres de los archivos de salida
CHILD_BIN = child.bin
PARENT_BIN = parent

# Objetivos (targets)
all: $(CHILD_BIN) $(PARENT_BIN) run

# Regla para compilar child.c en child.bin
$(CHILD_BIN): child.c
	$(CC) $(CFLAGS) -o $(CHILD_BIN) child.c

# Regla para compilar parent.c en parent
$(PARENT_BIN): parent.c
	$(CC) $(CFLAGS) -o $(PARENT_BIN) parent.c

# Regla para ejecutar el programa parent
run: $(PARENT_BIN)
	./$(PARENT_BIN)

# Limpiar los archivos generados
clean:
	rm -f $(CHILD_BIN) $(PARENT_BIN)

.PHONY: all clean run
