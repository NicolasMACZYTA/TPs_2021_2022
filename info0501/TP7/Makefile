CC = gcc
OBJETS = main.o graphe.o file.o plus_court_chemin.o sommet.o liste.o cellule.o pile.o tas.o tri.o ensemble.o file_priorites_min.o

mainTest: $(OBJETS)
	$(CC) -o mainTest $(OBJETS)

sommet.o : sommet.c sommet.h
	$(CC) -c sommet.c

pile.o: pile.c pile.h graphe.h
	$(CC) -c pile.c

graphe.o: graphe.c graphe.h liste.h file.h tri.h file_priorites_min.h sommet.h pile.h
	$(CC) -c graphe.c

file.o: file.c file.h graphe.h
	$(CC) -c file.c

tas.o: tas.c tas.h graphe.h
	$(CC) -c tas.c

tri.o: tri.c tri.h graphe.h tas.h
	$(CC) -c tri.c

liste.o : liste.c liste.h cellule.h
	$(CC) -c liste.c

cellule.o : cellule.c cellule.h
	$(CC) -c cellule.c

ensemble.o : ensemble.c ensemble.h graphe.h
	$(CC) -c ensemble.c

file_priorites_min.o: file_priorites_min.c file_priorites_min.h file.h
	$(CC) -c file_priorites_min.c

plus_court_chemin.o: plus_court_chemin.c plus_court_chemin.h graphe.h
	$(CC) -c plus_court_chemin.c
clean:
	rm mainTest $(OBJETS)