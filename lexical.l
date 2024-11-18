%{
    #include <stdio.h>

    void print_token(const char *type, const char *token){
        printf("%s : %s\n",type,token);
    }
%}

%%
"float" { print_token("keyword", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { print_token("Identifier", yytext); }
"+"|"*" { print_token("operator", yytext); }
"=" { print_token("operator", yytext); }
[ \t\n]+ {}
. {}
%%

int yywrap(){}

int main(){
    printf("Operators are:");
    yylex();
    return 0;
}
