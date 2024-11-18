#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to validate the syntax
int isValidSyntax(const char *input) {
    int length = strlen(input);
    if (length == 0) return 0; // Empty input is invalid

    for (int i = 0; i < length; i++) {
        // Check for invalid characters
        if (!isalpha(input[i]) && !isOperator(input[i]) && !isdigit(input[i])) {
            return 0; // Invalid character
        }

        // Check for operators at invalid positions
        if (isOperator(input[i])) {
            // Operator cannot be the first or last character
            if (i == 0 || i == length - 1) {
                return 0;
            }
            // Two consecutive operators are invalid
            if (isOperator(input[i - 1])) {
                return 0;
            }
        }
    }

    return 1; // Syntax is valid
}

int main() {
    char input[100];

    printf("Enter Syntax: ");
    scanf("%s", input);

    if (isValidSyntax(input)) {
        printf("%s is a valid syntax\n", input);
    } else {
        printf("%s is an invalid syntax\n", input);
    }

    return 0;
}
