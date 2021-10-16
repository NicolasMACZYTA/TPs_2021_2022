#include "strangeFunction.h"
#include <stdio.h>
#include <time.h>

size_t size_string(const char* str){
    const char *ptr = str;
    while(*ptr!='\0'){
        ptr=ptr+sizeof(char);
    }
    return (ptr-str)/sizeof(char);
}

int main(){
    clock_t start1, start2, end1, end2, total1, total2; 
    int i;
    start1 = clock();
    size_string("truc");
    for(i=0; i< 10000000; i++) {
   }
    end1 = clock();

    total1=(double)(end1-start1);
    printf("temps d'execution de size_string en milisecondes %ld\n",total1);
    return 0;
}