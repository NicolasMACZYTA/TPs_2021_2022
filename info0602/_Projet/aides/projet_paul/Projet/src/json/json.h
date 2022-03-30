#ifndef JSON

#define JSON

/* Déclarations des types constituant un objet JSON */
typedef struct{
    char* name;
    union{
        int entier;
        int boolean;
        double decimale;
        char* chaine;
    }value;
}json_champ_t;

typedef struct{
    json_champ_t* content;
}json_array_t;

typedef struct json_object_t{
    json_champ_t* json_fields;
    json_array_t* json_arrays;
    struct json_object_t* json_objects;
    struct json_object_t* pere;
}json_object_t;

/**
 * Permet d'initialiser un champ json de type entier à l'aide de son nom et sa valeur.
 * @return la référence du champ ainsi créé.
*/
json_champ_t* json_create_int_field(char* name, int entier);

/**
 * Permet d'initialiser un champ json de type décimale à l'aide de son nom et sa valeur.
 * @return la référence du champ ainsi créé.
*/
json_champ_t* json_create_decimale_field(char* name, double decimale);

/**
 * Permet d'initialiser un champ json de type boolean à l'aide de son nom et sa valeur.
 * @return la référence du champ ainsi créé.
*/
json_champ_t* json_create_bool_field(char* name, char* str);

/**
 * Permet d'initialiser un champ json de type string à l'aide de son nom et sa valeur.
 * @return la référence du champ ainsi créé.
*/
json_champ_t* json_create_string_field(char* name, char* str);

/**
 * Ajoute un champ json du type entier, décimale, boolean ou chaîne de caractères à un objet JSON.
 * @return 1 si l'ajout c'est effectuer sans problème, 0 sinon.
*/
int json_add_champ(json_object_t* obj, json_champ_t champ);

/**
 * Ajoute un champ json du type array à un objet JSON.
 * @return 1 si l'ajout c'est effectuer sans problème, 0 sinon.
*/
int json_add_array(json_object_t* obj, json_array_t* str);

/**
 * Ajoute un champ json du type objet à un objet JSON.
 * @return 1 si l'ajout c'est effectuer sans problème, 0 sinon.
*/
int json_add_object(json_object_t* obj, json_object_t* new_obj);

/**
 * Procédure permettant de voir le contenue d'un objet JSON.
*/
void json_afficher(json_object_t* obj);

#endif