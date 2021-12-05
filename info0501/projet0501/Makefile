CC = gcc -Wall -O3
OBJETS = test.o cellule.o liste.o graphe.o file.o ensemble.o plus_court_ch.o

test : $(OBJETS)
	$(CC) -o test $(OBJETS) -g

prog_liste.o : test.c liste.h
	$(CC) -c test.c -g

cellule.o : cellule.c cellule.h
	$(CC) -c cellule.c -g

liste.o : liste.c liste.h
	$(CC) -c liste.c -g

graphe.o : graphe.c graphe.h
	$(CC) -c graphe.c -g

file.o : file.c file.h
	$(CC) -c file.c -g

ensemble.o : ensemble.c ensemble.h
	$(CC) -c ensemble.c -g

plus_court_ch.o : plus_court_ch.c plus_court_ch.h
	$(CC) -c plus_court_ch.c -g


clean:
	rm test $(OBJETS)