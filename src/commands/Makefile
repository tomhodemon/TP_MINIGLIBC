C=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=$(f)
SRC=../mini_string.c ../mini_memory.c ../mini_io.c ../linked_list.c ../debug.c ./$(EXEC).c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -I../mini_lib.h

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)