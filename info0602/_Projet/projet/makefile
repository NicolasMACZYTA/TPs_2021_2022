CC = gcc -Wall -O3
OBJETS = auto2latex.o aidechar.o

auto2latex : $(OBJETS)
	$(CC) -o auto2latex $(OBJETS)

auto2latex.o : auto2latex.c aidechar.c aidechar.h
	$(CC) -c auto2latex.c

autodet : $(OBJETS)
	$(CC) -o autodet $(OBJETS)

autodet.o : autodet.c aidechar.c aidechar.h
	$(CC) -c autodet.c

aidechar.o : aidechar.c aidechar.h
	$(CC) -c aidechar.c

clean:
	rm prog_liste $(OBJETS)