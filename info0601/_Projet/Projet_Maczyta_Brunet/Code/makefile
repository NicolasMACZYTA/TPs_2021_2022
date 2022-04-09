EXEC = main_prog client serveur
OBJETS = ihm_ncurses.o fichier.o
NOM_PROJET = jeuaventure

.SUFFIXES: .c .o

EXEC_O = $(EXEC:=.o)
OBJETS_O = $(OBJETS) $(EXEC_O)
CC = gcc
CCFLAGS_STD = -Wall -O3 -ansi -pedantic -Werror
CCFLAGS = $(CCFLAGS_STD)

all: msg $(OBJETS) $(EXEC_O)
	@echo "Creation des executables..."
	@for i in $(EXEC); do \
	$(CC) -o $$i $$i.o $(OBJETS) -lncurses -pthread; \
	done
	@echo "Termine."

msg:
	@echo "Creation des objets..."

debug: CCFLAGS = $(CCFLAGS_STD)
debug: all

.c.o: .h
	@cd $(dir $<) && ${CC} ${CCFLAGS} -c $(notdir $<) -o $(notdir $@)

clean:
	@echo "Suppresion des objets, des fichiers temporaires..."
	@rm -f $(OBJETS) $(EXEC_O)
	@rm -f *~ *#
	@rm -f $(EXEC)
	@rm -f dependances
	@echo "Termine."

depend:
	@echo "Creation des dependances..."
	@sed -e "/^# DEPENDANCES/,$$ d" makefile > dependances
	@echo "# DEPENDANCES" >> dependances
	@for i in $(OBJETS_O); do \
	$(CC) -MM -MT $$i $(CCFLAGS) `echo $$i | sed "s/\(.*\)\\.o$$/\1.c/"` >> dependances; \
	done
	@cat dependances > makefile
	@rm dependances
	@echo "Termine."

ARCHIVE_FILES = *

archive: clean
	@echo "Creation de l'archive $(NOM_PROJET)$(shell date '+%y%m%d.tar.gz')..."
	@REP=`basename "$$PWD"`; cd .. && tar zcf $(NOM_PROJET)$(shell date '+%y%m%d.tar.gz') $(addprefix "$$REP"/,$(ARCHIVE_FILES))
	@echo "Termine."

# DEPENDANCES
ihm_ncurses.o: ihm_ncurses.c ihm_ncurses.h
fichier.o: fichier.c fichier.h

main_prog.o: main_prog.c fichier.h ihm_ncurses.h
client.o: client.c fichier.h ihm_ncurses.h
serveur.o: serveur.c fichier.h