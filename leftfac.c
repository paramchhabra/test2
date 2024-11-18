#include <stdio.h>
#include <string.h>

void removeLeftFactoring(char nonTerminal, char production[]) {
    char commonPrefix[20], remaining1[20], remaining2[20];
    int i = 0, j = 0, k = 0, l = 0;

    // Split the productions at the `/` operator
    char first[20], second[20];
    while (production[i] != '/' && production[i] != '\0') {
        first[j++] = production[i++];
    }
    first[j] = '\0'; // End the first production

    if (production[i] == '/') i++; // Skip `/`

    while (production[i] != '/' && production[i] != '\0') {
        second[k++] = production[i++];
    }
    second[k] = '\0'; // End the second production

    // Find common prefix between first and second productions
    i = 0;
    while (first[i] != '\0' && second[i] != '\0' && first[i] == second[i]) {
        commonPrefix[l++] = first[i++];
    }
    commonPrefix[l] = '\0'; // End common prefix

    // Separate the remaining parts
    strcpy(remaining1, &first[i]);  // Remaining part of the first production
    strcpy(remaining2, &second[i]); // Remaining part of the second production

    // Output the transformed grammar
    printf("%c -> %s%c'\n", nonTerminal, commonPrefix, nonTerminal);
    printf("%c' -> %s / %s / ∈\n", nonTerminal, remaining1, remaining2);
}

int main() {
    char production1[50], production2[50];
    char nonTerminal1, nonTerminal2;

    printf("Enter the first production (e.g., S->iEtS/iEtSeS/a): ");
    scanf("%s", production1);
    printf("Enter the second production (e.g., E->b): ");
    scanf("%s", production2);

    nonTerminal1 = production1[0];
    nonTerminal2 = production2[0];

    printf("The productions after removing Left Factoring are:\n");
    removeLeftFactoring(nonTerminal1, &production1[3]); // Process the first production
    printf("%c -> %s\n", nonTerminal2, &production2[3]); // Print the second production unchanged

    return 0;
}
