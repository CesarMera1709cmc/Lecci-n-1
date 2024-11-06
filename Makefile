
CC = gcc
CFLAGS = -Wall -g
OBJ = main.o datos.o menu.o
PROGRAMA = TAERA1

all: $(PROGRAMA)

$(PROGRAMA): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROGRAMA) $(OBJ)

main.o: main.c menu.h
	$(CC) $(CFLAGS) -c main.c

datos.o: datos.c datos.h
	$(CC) $(CFLAGS) -c datos.c

menu.o: menu.c menu.h datos.h
	$(CC) $(CFLAGS) -c menu.c
clean:
	rm -f $(OBJ) $(PROGRAMA)

