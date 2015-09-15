CC=gcc
FLAGS= -W -Wall
SRC= creation_graphe.c parcours_graphe.c creation_finale.c main.c
OBJ= $(SRC:.c=.o)

freydi:	$(OBJ)
	$(CC) $^ -o $@ $(FLAGS)

%.o:	%.c
	$(CC) -c -o $@ $^ $(FLAGS)

clean:	
	rm $(OBJ) *~ *#
