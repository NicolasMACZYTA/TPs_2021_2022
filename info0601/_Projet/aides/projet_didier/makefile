all:game verif aventure
aventure:gameplay.o aventure.o
	gcc -g -O3 -Wall -Werror -ansi -pedantic aventure.o gameplay.o -o aventure -lncurses -lpthread
verif:gameplay.o verif_map.o
	gcc -g -O3 -Wall -Werror -ansi -pedantic verif_map.o gameplay.o -o verif -lncurses -lpthread
game:gameplay.o test_gameplay.o
	gcc -g -O3 -Wall -Werror -ansi -pedantic test_gameplay.o gameplay.o -o game -lncursesw -lpthread
aventure.o:aventure.c gameplay.h
	gcc -g -O3 -Wall -Werror -ansi -pedantic -c aventure.c
gameplay.o:gameplay.c gameplay.h
	gcc -g -O3 -Wall -Werror -ansi -pedantic -c gameplay.c
verif_map.o:verif_map.c gameplay.h
	gcc -g -O3 -Wall -Werror -ansi -pedantic -c verif_map.c
test_gameplay.o:test_gameplay.c gameplay.h
	gcc -g -O3 -Wall -Werror -ansi -pedantic -c test_gameplay.c
clean:
	rm -f aventure game verif gameplay.o aventure.o test_gameplay.o verif_map.o
	rm *~
