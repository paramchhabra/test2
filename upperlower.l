%{
    #include <stdio.h>
    int lower = 0;
    int upper = 0;
%}

%% 
[A-Z]   { upper++; }         // Matches uppercase letters and increments `upper`
[a-z]   { lower++; }         // Matches lowercase letters and increments `lower`
.|\n    { /* Do nothing for any other character */ }
%%

int yywrap(void) {
    return 1; // End of input stream
}

int main() {
    yylex();  // Run lexical analyzer
    printf("Upper: %d\n", upper);  // Print number of uppercase letters
    printf("Lower: %d\n", lower);  // Print number of lowercase letters
    return 0;
}
