#include <stdio.h>
#include <string.h>

void eliminateLeftRecursion(char nonTerminal, char production[]) {
    char alpha[20], beta[20];
    int i = 0, j = 0, k = 0;
    int hasLeftRecursion = 0;

    // Check for left recursion
    if (production[0] == nonTerminal) {
        hasLeftRecursion = 1;
        i = 1;
        while (production[i] != '\0' && production[i] != '|') {
            alpha[j++] = production[i++];
        }
        alpha[j] = '\0'; // End alpha string

        if (production[i] == '|') i++;
        while (production[i] != '\0') {
            beta[k++] = production[i++];
        }
        beta[k] = '\0'; // End beta string
    }

    // Output the transformed grammar
    if (hasLeftRecursion) {
        printf("%c -> %s%c'\n", nonTerminal, beta, nonTerminal);
        printf("%c' -> %s%c'|ep\n", nonTerminal, alpha, nonTerminal);
    } else {
        printf("No Left Recursion detected for %c -> %s\n", nonTerminal, production);
    }
}

int main() {
    char production[50];
    char nonTerminal;

    printf("Enter the production (e.g., E->E+E|T): ");
    scanf("%s", production);

    nonTerminal = production[0];

    printf("The productions after eliminating Left Recursion are:\n");
    eliminateLeftRecursion(nonTerminal, &production[3]); // Start from the RHS

    return 0;
}
