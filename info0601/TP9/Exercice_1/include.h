#ifndef _INCLUDE_
#define _INCLUDE_

#define CLE                1978    // Clé pour le segment de mémoire partagé
#define HAUTEUR              20    // Hauteur min. pour l'interface
#define LARGEUR              20    // Largeur min. pour l'interface

#define VITESSE         1000000    // Vitesse de raffraîchissement

// Pour savoir si un virus est créé, une valeur aléatoire dans [0; INTERVALLE]
// est générée. Si elle est inférieure à CREATION, un nouveau virus est créé
#define INTERVALLE          100
#define CREATION              2

#endif