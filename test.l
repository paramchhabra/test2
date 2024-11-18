%{
#include <stdio.h>

%}
%%
. {printf("%s",yytext);}

%%
int main() {
    yylex();

    return 0;
}

int yywrap() {
    return 1; // Indicate no more files to process
}