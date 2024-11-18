%{
#include <stdio.h>
#include <ctype.h>

int result = 0;
int current_value = 0;
char current_op = '+';

void apply_operation() {
    switch (current_op) {
        case '+': result += current_value; break;
        case '-': result -= current_value; break;
        case '*': result *= current_value; break;
        case '/': result /= current_value; break;
    }
}
%}
%%
[0-9]+ {
    current_value = atoi(yytext);
    apply_operation();
}
[+\-*/] {
    current_op = yytext[0];
}
[()] {
    // Just ignoring the parentheses for simplicity in this example.
}
[ \t\n]+ {
    /* Ignore whitespace */
}
%%
int main() {
    printf("Enter the Expression: ");
    yylex();
    printf("Output: %d\n", result);
    return 0;
}

int yywrap(void) {
    return 1;
}