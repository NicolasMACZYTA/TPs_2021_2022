#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

int main(int argc, char *argv[]) {
    FILE *f;
    wint_t c;
    
    if(argc != 2) {
        fprintf(stderr, "Usage : %s fichier\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    setlocale(LC_ALL, "en_US.UTF-8");
    
    if((f = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier '%s' ", argv[1]);
        perror("");
        exit(EXIT_FAILURE);
    }
    
    while((c = fgetwc(f)) != WEOF) {
        printf("%lc", c);
    }
    
    if(fclose(f) == -1) {
        perror("Erreur lors de la fermeture du fichier ");
        exit(EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}