#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "include.h"

/**
 * Génère un entier aléatoire dans un intervalle [a, b].
 * @param a la borne minimale
 * @param b la borne maximale
 * @return l'entier aléatoire
 */
int alea(int a, int b) {
    return rand() % (b - a + 1) + a;
}

/**
 * Simulation d'un bloc de code d'un fils.
 * @param fd le descripteur du tube en écriture vers le père.
 * @param num le numéro du bloc
 */
void bloc(int fd, int num) {
    message_t msg;

    // Message pour avertir du début
    msg.num = num;
    msg.action = DEBUT;
    if(write(fd, &msg, sizeof(msg)) == -1) {
        fprintf(stderr, "Erreur lors de l'écriture vers le père (1)");
        perror(" ");
        exit(EXIT_FAILURE);
    }

    // Pause pour simuler l'exécution du bloc
    usleep(alea(MIN, MAX));

    // Message pour avertir de la fin
    msg.action = FIN;
    if(write(fd, &msg, sizeof(msg)) == -1) {
        fprintf(stderr, "Erreur lors de l'écriture vers le père (2)");
        perror(" ");
        exit(EXIT_FAILURE);
    }
}

/**
 * Routine du fils 1.
 * @param fd le descripteur du tube en écriture vers le père.
 */
void fils1(int fd) {
    usleep(alea(MIN, MAX));

    // Bloc A1
    bloc(fd, A1);
    // Fin bloc A1

    usleep(alea(MIN, MAX));

    // Bloc B1
    bloc(fd, B1);
    // Fin bloc B1

    usleep(alea(MIN, MAX));

    // Bloc C1
    bloc(fd, C1);
    // Fin bloc C1

    if(close(fd) == -1) {
        perror("Erreur lors de la fermeture du tube (fils 1) ");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

/**
 * Routine du fils 2.
 * @param fd le descripteur du tube en écriture vers le père. 
 */
void fils2(int fd) {
    usleep(alea(MIN, MAX));

    // Bloc A2
    bloc(fd, A2);
    // Fin bloc A2

    usleep(alea(MIN, MAX));

    // Bloc B2
    bloc(fd, B2);
    // Fin bloc B2

    usleep(alea(MIN, MAX));

    // Bloc C2
    bloc(fd, C2);
    // Fin bloc C2

    if(close(fd) == -1) {
        perror("Erreur lors de la fermeture du tube (fils 2) ");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

/**
 * Routine du fils 3.
 * @param fd le descripteur du tube en écriture vers le père.
 */
void fils3(int fd) {
    usleep(alea(MIN, MAX));

    // Bloc A3
    bloc(fd, A3);
    // Fin bloc A3

    usleep(alea(MIN, MAX));

    // Bloc B3
    bloc(fd, B3);
    // Fin bloc B3

    usleep(alea(MIN, MAX));

    // Bloc C3
    bloc(fd, C3);
    // Fin bloc C3
    
    if(close(fd) == -1) {
        perror("Erreur lors de la fermeture du tube (fils 2) ");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

/**
 * Fonction principale.
 * @param argc le nombre d'arguments
 * @param argv les arguments
 * @return le code de retour
 */
int main(int argc, char *argv[]) {
    int i, n, erreur, erreurs = 0;
    pid_t tube[2];
    char *blocs[9] = { "A1", "B1", "C1", "A2", "B2", "C2", "A3", "B3", "C3" };
    int etats[9];
    message_t msg;

    // Initialisation des états
    for(i = 0; i < 9; i++)
        etats[i] = UNDEF;

    // Création du tube des fils vers le père
    if(pipe(tube) == -1) {
        perror("Erreur lors de la création du tube ");
        exit(EXIT_FAILURE);
    }

    // Création des fils
    for(i = 1; i <= 3; i++) {
        n = fork();
        if(n == -1) {
            fprintf(stderr, "Erreur lors de la creation du fils %d", i);
            perror(" ");
            exit(EXIT_FAILURE);
        }
        else if(n == 0) {
            // Fermeture du descripteur inutile
            if(close(tube[LECTURE]) == -1) {
                fprintf(stderr, "Erreur lors de la fermeture du tube en lecture dans le fils %d\n", i);
                exit(EXIT_FAILURE);
            }

            // Initialisation du générateur de nombres pseudo-aléatoire
            srand(time(NULL) + getpid());

            // Lancement des routines des fils
            switch(i) {
                case 1: fils1(tube[ECRITURE]); break;
                case 2: fils2(tube[ECRITURE]); break;
                case 3: fils3(tube[ECRITURE]); break;
            }
        }
    }

    // Fermeture du tube en écriture pour le père
    if(close(tube[ECRITURE]) == -1) {
        fprintf(stderr, "Erreur lors de la fermeture du tube en lecture dans le père\n");
        exit(EXIT_FAILURE);
    }

    // Lecture des actions : nombre de blocs x 2
    for(i = 0; i < 18; i++) {
        // Lecture de l'action
        if(read(tube[LECTURE], &msg, sizeof(msg)) == -1) {
            perror("Erreur lors de la lecture du message dans le père ");
            exit(EXIT_FAILURE);
        }

        // Affichage de l'action
        if(msg.action == DEBUT) {
            // Vérification des actions
            erreur = 0;
            switch(msg.num) {
                case A1:
                    erreur = (etats[B2] == DEBUT) || (etats[A3] == DEBUT);
                    break;
                case A3:
                    erreur = (etats[A1] == DEBUT) || (etats[B2] == DEBUT);
                    break;
                case B2:
                    erreur = (etats[A1] == DEBUT) || (etats[A3] == DEBUT);
                    break;
                case C1:
                    erreur = (etats[B2] != FIN) || (etats[C3] != FIN);
                    break;
                case C3:
                    erreur = (etats[B2] != FIN);
                    break;
            }

            // Affichage de l'état
            printf("Début du bloc %s ", blocs[msg.num]);
            if(erreur) {
                erreurs++;
                printf("\033[0;31m[ERREUR]\033[0m\n");
            }
            else
                printf("\033[0;32m[OK]\033[0m\n");
        }
        else
            printf("Fin du bloc %s\n", blocs[msg.num]);
        etats[msg.num] = msg.action;
    }

    // Attente de la fin des fils
    for(i = 0; i < 3; i++) {
        if(wait(NULL) == -1) {
            perror("Erreur lors de la fin d'un fils ");
            exit(EXIT_FAILURE);
        }
    }

    // Message de fin
    if(erreurs != 0)
        printf("L'exécution a échoué (c'est nul !!!).\n");
    else
        printf("L'exécution a réussie (pour cette fois).\n");

    return EXIT_SUCCESS;
}