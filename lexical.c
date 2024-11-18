#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to check if the token is a keyword
int isKeyword(const char *token) {
    const char *keywords[] = {"float", "int", "char", "double", "void", "return", "if", "else", "for", "while"};
    for (int i = 0; i < 10; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1; // Token is a keyword
        }
    }
    return 0; // Token is not a keyword
}

// Function to check if the token is an identifier
int isIdentifier(const char *token) {
    if (token[0] == '\0' || !isalpha(token[0])) {
        return 0; // Empty or does not start with a letter
    }
    for (int i = 0; token[i] != '\0'; i++) {
        if (!isalnum(token[i]) && token[i] != '_') {
            return 0; // Invalid character in identifier
        }
    }
    return 1; // Valid identifier
}

// Function to check if the character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
            ch == '<' || ch == '>');
}

// Function to perform lexical analysis
void lex_analysis(const char *input) {
    int n = strlen(input);
    int i = 0;
    while (i < n) {
        char ch = input[i];

        // Skip white spaces
        if (isspace(ch)) {
            i++;
            continue;
        }

        // If the character is alphabetic, process it as a token
        if (isalpha(ch)) {
            char token[100];
            int j = 0;
            while ((isalnum(ch) || ch == '_') && i < n) {
                token[j++] = ch;
                i++;
                ch = input[i];
            }
            token[j] = '\0'; // Null-terminate the token

            // Check if the token is a keyword or identifier
            if (isKeyword(token)) {
                printf("Keyword: %s\n", token);
            } else if (isIdentifier(token)) {
                printf("Identifier: %s\n", token);
            } else {
                printf("Unknown: %s\n", token);
            }
        }
        // If the character is an operator
        else if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
            i++;
        }
        // If the character is anything else
        else {
            printf("Unknown: %c\n", ch);
            i++;
        }
    }
}

int main() {
    // Open the input file
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    // Read the input from the file
    char input[1000];
    fgets(input, sizeof(input), inputFile);
    fclose(inputFile);

    // Perform lexical analysis
    lex_analysis(input);

    return 0;
}
