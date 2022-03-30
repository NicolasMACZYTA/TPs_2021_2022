analyseur_json : y.tab.o lex.yy.o json.o
	gcc -o analyseur_json y.tab.o lex.yy.o json.o -lm -lfl

y.tab.o : y.tab.h y.tab.c
	gcc -c y.tab.c

y.tab.c y.tab.h : json.yacc.y
	yacc -vd -d json.yacc.y

lex.yy.o : lex.yy.c y.tab.h
	gcc -c lex.yy.c

lex.yy.c : json.lex 
	flex json.lex

json.o: json.c json.h
	gcc -c json.o json.c json.h

clean:
	rm -f y.tab.*
	rm -f lex.yy.*
	rm -f json json.exe
	rm -f *~
	rm -f *.stackdump