#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <ncurses.h>

#include "include.h"

#define xstr(s) str(s)
#define str(s) #s

int main(int argc, char *argv[]) {
    char buf[MAX_MSG];
    bool quitter = FALSE;
    char c;
    
    // Récupération de la file de messages
    // #TODO#
    
    printf("Saissez des messages ; #QUITTE# pour quitter le client, #STOP# pour arrêter le visualiseur\n");
    while(quitter == FALSE) {
        printf("Saisir un message : ");
        if(scanf("%"xstr(MAX_MSG)"[^\n]", buf) != 1) {
            fprintf(stderr, "Aïe, je n'ai rien à lire...\n");
            exit(EXIT_FAILURE);
        }
        while(((c = getchar()) != '\n') || (c == EOF));
        
        if(strcmp(buf, "#QUITTE#") == 0)
            quitter = TRUE;
        else {
            // Envoi du message au serveur
            // #TODO#
            printf("Message envoyé.\n");
            
            if(strcmp(buf, "#STOP#") == 0)
                quitter = TRUE;
        }
    }
    
    return EXIT_SUCCESS;
}