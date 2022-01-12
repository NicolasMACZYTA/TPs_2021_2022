

typedef struct pile{
    int * tab;
    int pos;
    int size;
}pile;

pile* initialiser(int taille);
int pile_vide(pile*p);
int pile_pleine(pile*p);
void empiler(pile*p,int value);
int depiler(pile*p);
void afficher_pile(pile*p);
void vider_pile(pile*p);