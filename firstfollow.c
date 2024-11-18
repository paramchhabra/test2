#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

char productions[MAX][MAX];
char first[MAX][MAX];
char follow[MAX][MAX];
int num_productions;

// Function to find First of a symbol
void findFirst(char result[], char symbol) {
    if (!isupper(symbol)) {
        strncat(result, &symbol, 1); // If symbol is terminal, add it to First
        return;
    }

    for (int i = 0; i < num_productions; i++) {
        if (productions[i][0] == symbol) {
            // If production starts with terminal or epsilon
            if (!isupper(productions[i][2]) || productions[i][2] == '#') {
                strncat(result, &productions[i][2], 1);
            } else {
                // Recursively find First of the next symbol
                findFirst(result, productions[i][2]);
            }
        }
    }
}

// Function to find Follow of a symbol
void findFollow(char result[], char symbol) {
    if (productions[0][0] == symbol) {
        strcat(result, "$"); // Add $ for the start symbol
    }

    for (int i = 0; i < num_productions; i++) {
        char *pos = strchr(productions[i], symbol);
        if (pos != NULL) {
            int idx = (int)(pos - productions[i]);
            if (productions[i][idx + 1] != '\0') {
                // If there is a symbol after the current symbol
                char first_of_next[MAX] = "";
                findFirst(first_of_next, productions[i][idx + 1]);
                for (int j = 0; j < strlen(first_of_next); j++) {
                    if (first_of_next[j] != '#') { // Add First to Follow
                        strncat(result, &first_of_next[j], 1);
                    } else {
                        // If epsilon in First, recursively find Follow of LHS
                        findFollow(result, productions[i][0]);
                    }
                }
            } else if (productions[i][idx + 1] == '\0' && productions[i][0] != symbol) {
                // If at the end, add Follow of LHS to Follow of symbol
                findFollow(result, productions[i][0]);
            }
        }
    }
}

// Remove duplicates from a string
void removeDuplicates(char *str) {
    int len = strlen(str);
    char temp[MAX] = "";
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (!strchr(temp, str[i])) {
            temp[index++] = str[i];
        }
    }
    temp[index] = '\0';
    strcpy(str, temp);
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &num_productions);

    printf("Enter the productions (e.g., S->AB or A->a):\n");
    for (int i = 0; i < num_productions; i++) {
        scanf("%s", productions[i]);
    }

    // Calculate First sets
    for (int i = 0; i < num_productions; i++) {
        char result[MAX] = "";
        findFirst(result, productions[i][0]);
        removeDuplicates(result);
        strcpy(first[i], result);
    }

    // Calculate Follow sets
    for (int i = 0; i < num_productions; i++) {
        char result[MAX] = "";
        findFollow(result, productions[i][0]);
        removeDuplicates(result);
        strcpy(follow[i], result);
    }

    // Display First and Follow sets
    printf("\nFirst and Follow Sets:\n");
    for (int i = 0; i < num_productions; i++) {
        printf("First(%c) = { %s }\n", productions[i][0], first[i]);
    }
    for (int i = 0; i < num_productions; i++) {
        printf("Follow(%c) = { %s }\n", productions[i][0], follow[i]);
    }

    return 0;
}
