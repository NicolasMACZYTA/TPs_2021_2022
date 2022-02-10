#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include "fonctions.h"
#include "fenetre.h"
#include "include.h"

int main(int argc, char *argv[]) {
    bool quitter = FALSE;
    fenetre_t *win;
    char buf[MAX_MSG];
    
    // Initialisation de ncurses
    setlocale(LC_ALL, "");
    ncurses_init();
    ncurses_initsouris();
    ncurses_couleurs(); 
    palette();
    clear();
    refresh();  
    
    // Vérification des dimensions du terminal
    if((COLS < LARGEUR) || (LINES < HAUTEUR)) {
        ncurses_stop();
        fprintf(stderr, 
              "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", 
              COLS, LINES, LARGEUR, HAUTEUR);
        exit(EXIT_FAILURE);
    }
    
    // Création de la fenêtre pour afficher les messages
    win = fenetre_creer(0, 0, COLS, HAUTEUR, "Messages", TRUE);
    
    // Récupération/création de la file de messages
    // #TODO#
    
    // Boucle principale
    while(quitter == FALSE) {
        // Lecture du prochain message
        // #TODO#
        
        if(strcmp(buf, "#STOP#") == 0) {            
            quitter = TRUE;
            fenetre_printw(win, "Demande d'arrêt reçu...\n");
            fenetre_refresh(win);
            sleep(5);
        }
        else {
            // Affichage du message
            fenetre_printw(win, "%s\n", buf);
            fenetre_refresh(win);
        }
    }
    
    // Arrêt de ncurses
    fenetre_supprimer(&win);
    ncurses_stop();

    // Suppression de la file
    // #TODO#
    printf("File supprimée.\n");

    return EXIT_SUCCESS;    
}