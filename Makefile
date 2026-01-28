CC = gcc
CFLAGS = -Wall -g

# Diretórios
INCLUDES_DIR = includes
SRC_DIR = src

# Arquivos de origem
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

# Nome do executável
EXECUTABLE = zenfile

# Regra padrão para compilar o executável
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Regra para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)