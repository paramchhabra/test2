#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char lhs[10];
    char rhs[50];
} Statement;

void optimizeCode(Statement statements[], int n) {
    printf("\n// Optimized Code:\n");
    for (int i = 0; i < n; i++) {
        // Constant Folding: Simplify constant expressions in RHS
        char *rhs = statements[i].rhs;
        int val1, val2;
        char op;
        if (sscanf(rhs, "%d %c %d", &val1, &op, &val2) == 3) {
            int result;
            switch (op) {
                case '+': result = val1 + val2; break;
                case '-': result = val1 - val2; break;
                case '*': result = val1 * val2; break;
                case '/': if (val2 != 0) result = val1 / val2; break;
                default: continue;
            }
            sprintf(statements[i].rhs, "%d", result); // Replace RHS with result
        }

        // Eliminate Redundant Assignments
        int redundant = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(statements[i].lhs, statements[j].lhs) == 0 &&
                strcmp(statements[i].rhs, statements[j].rhs) == 0) {
                redundant = 1;
                break;
            }
        }

        if (!redundant) {
            printf("%s = %s;\n", statements[i].lhs, statements[i].rhs);
        }
    }
}

int main() {
    int n;
    Statement statements[MAX];

    printf("Enter the number of statements: ");
    scanf("%d", &n);

    printf("Enter the statements (e.g., a = b + c):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s = %[^\n]s", statements[i].lhs, statements[i].rhs);
    }

    printf("\n// Input Code:\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s;\n", statements[i].lhs, statements[i].rhs);
    }

    optimizeCode(statements, n);

    return 0;
}
