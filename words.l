%{
    #include <stdio.h>
    int wordcount = 0;
%}

%%
[a-zA-Z0-9]+ {wordcount++;}
[\t\n]+ ;
%%

int yywrap(){}

int main(){
    yylex();
    printf("Number of words %d\n",wordcount);
    return 0;
}