#ifndef AUTOMATE_H
#define AUTOMATE_H

typedef struct liste_type{
    //?
    struct liste_type *pred;
    struct liste_type *succ;
}liste_t;

typedef struct automate_type{
    char nodeStart[10];
    char nodeEnd[50];
    char alphabet[50];
    char type[6];
    struct liste_type *liens;
}automate_t;

int init_automate(automate_t *a, char *t);

#endif /* AUTOMATE_H */