#ifndef FICHIER_H
#define FICHIER_H

char * hex_from_buf(char*buf);
void string2hexString(char* input, char* output);
char * to_string(char*buf,int offset);
char * to_disp(char*buf);
void lire_buf(int fd, char*buf, int offset);
void ecrire_buf(int fd, char*buf, int offset);
void supprimer_octet(int fd, int selection, int offset,int size);
char * num_ligne(int num);
int creer_fichier(char * nomfichier, int taillegrille, int nb_grilles, int nb_monstres);
int sauvegarder_carte(char * nomfichier, char* buf1,char*buf2,int *buf3,int taillegrille, int nbmonstres);

#endif