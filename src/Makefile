C=gcc
CFLAGS=-Wall
LDFLAGS=
C_SOURCES=$(wildcard *.c)
NO_EXEC_C_SOURCES=debug.c mini_string.c mini_memory.c mini_io.c linked_list.c
EXEC_C_EXECUTABLE=$(filter-out $(NO_EXEC_C_SOURCES), $(C_SOURCES))
EXEC=$(EXEC_C_EXECUTABLE:.c=)
OBJ= $(C_SOURCES:.c=.o)
NO_EXEC_OBJ=debug.o mini_string.o mini_memory.o mini_io.o linked_list.o

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $(NO_EXEC_OBJ) $@.o $(LDFLAGS) 

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -I./mini_lib.h

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)