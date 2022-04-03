#ifndef CHARFUNCS_H
#define CHARFUNCS_H

void delStr(char *string, char *sub);
int compteChar(char str[], char ch);
char *replaceChar(char *str, char *a, char *b);
void templateCopy(FILE* f);
char *replaceSymbole(char *str);
char** str_split(char* a_str, const char a_delim);
#endif /* CHARFUNCS_H */