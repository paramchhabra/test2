%{
    #include <stdio.h>
    int pan = 0;
    char firstchar = '';
%}

%%

[A-Z]{5}[0-9]{4}[A-z] {pan=1;}
%%

int yywrap(){}

int main(){
    yylex();
    if(pan==1){
        printf("Valid Pan\n");
    }
    else{
        printf("Invalid Pan\n");
    }
    return 0;
}