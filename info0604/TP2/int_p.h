#include <pthread.h>

typedef struct int_protege{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int valeur;
}int_p;