#include <stddef.h>
#include "cellule.h"

void initialiserCellule(cellule_t *c, int idSommet){

    c->pred=NULL;
    c->succ=NULL;
    c->idSommet=idSommet;
  
}
