C=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=app
SRC=./src/mini_string.c ./src/mini_memory.c ./src/mini_io.c ./src/main.c ./src/linked_list.c ./src/debug.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

app: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -I./src/mini_lib.h

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
