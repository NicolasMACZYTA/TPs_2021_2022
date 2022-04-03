%{
    #include <stdio.h>
    #include "y.tab.h"
%}
  
alpha   
    [A-Za-z_]
digit     
  [0-9]
%%
[\t \n] ;
void|bool|char|int|float|double           return TYPE;
{alpha}({alpha}|{digit})                 return ID;
              return yytext[0];
%H
 int yywrap()
{
    return 1;
}