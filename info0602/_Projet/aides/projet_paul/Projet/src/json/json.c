#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "json.h"

json_champ_t* json_create_int_field(char* name, int entier){
    json_champ_t* new_field;
    new_field->name = name;
    new_field->value.entier = entier;
    return new_field;
}

json_champ_t* json_create_decimale_field(char* name, double decimale){
    json_champ_t* new_field;
    new_field->name = name;
    new_field->value.decimale = decimale;
    return new_field;
}

json_champ_t* json_create_bool_field(char* name, char* str){
    json_champ_t* new_field;
    new_field->name = name;
    if(!strcmp("true", str))
        new_field->value.boolean = 1;
    else
        new_field->value.boolean = 0;
    return new_field;
}

json_champ_t* json_create_string_field(char* name, char* str){
    json_champ_t* new_field;
    new_field->name = name;
    strcpy(new_field->value.chaine, str);
    return new_field;
}

int json_add_champ(json_object_t* obj, json_champ_t champ){
    json_champ_t* tmp;

    /* Si la liste des champs est nil, allocation, sinon réallocation */
    if(obj->json_fields == NULL) 
        tmp = (json_champ_t*)malloc(sizeof(json_champ_t));
    else
        tmp = (json_champ_t*)realloc(obj->json_fields, sizeof(obj->json_fields) +  sizeof(json_champ_t));
    
    /* Si tmp est nil, alors erreur, retourne 0, sinon affectation de la nouvelle liste puis retourne 1 */
    if(tmp == NULL)
        return 0;
    else{
        tmp[sizeof(tmp)/sizeof(json_champ_t)] = champ;
        obj->json_fields = tmp;
        return 1;
    }
}

void json_afficher(json_object_t* obj){
    int i;
    
    printf("Liste des champs de l'objet : \n");
    for(i = 0; i < sizeof(obj->json_fields)/sizeof(json_champ_t); i++){
        printf("\t- Champ : %s, Valeur : %s\n", obj->json_fields[i].name, obj->json_fields[i].value);
    }
}