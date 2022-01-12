EXECUTABLE = exo1

LEX = flex
LEXFLAGS = 
LEXLIB = -lfl

$(EXECUTABLE): lex.yy.o	pile.o
	gcc -o $(EXECUTABLE) lex.yy.o pile.o $(LEXLIB) -W -Wall

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

pile.o: pile.c pile.h
	gcc -c pile.c

lex.yy.c: $(EXECUTABLE:=.lex)
	$(LEX) $(LEXFLAGS) $(EXECUTABLE:=.lex) 

clean:
	rm -f *~ \#* *.o
	rm -f $(EXECUTABLE) $(EXECUTABLE:=.exe)
	rm -f *.core *.stackdump
	rm -f lex.yy.c lex.yy.o
	rm -f pile.o
