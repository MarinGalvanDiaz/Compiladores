# --- Compilador y opciones ---
CC = gcc
CFLAGS = -Wall -g -lm

# --- Archivos fuente ---
OBJS = vector.tab.o lex.yy.o init.o math.o symbol.o error.o
HDRS = hoc.h

# --- Regla principal ---
all: vector

# --- Generar ejecutable ---
vector: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# --- Generar parser con Bison ---
vector.tab.c vector.tab.h: vector.y
	bison -d vector.y

# --- Generar analizador léxico con Flex ---
lex.yy.c: vector.l vector.tab.h
	flex vector.l

# --- Compilar módulos ---
%.o: %.c $(HDRS)
	$(CC) -c $< -o $@ $(CFLAGS)

# --- Limpiar archivos intermedios ---
clean:
	rm -f *.o vector.tab.c vector.tab.h lex.yy.c vector

# --- Limpiar y recompilar todo ---
rebuild: clean all
