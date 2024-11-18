#include <stdio.h>
#include <string.h>

typedef struct {
    char lhs[10];
    char op1[10];
    char operator;
    char op2[10];
} Quadruple;

void generateCode(Quadruple quads[], int n) {
    int regCount = 0;

    for (int i = 0; i < n; i++) {
        if (quads[i].operator == '-') {
            printf("MOV %s, R%d\n", quads[i].op1, regCount);
            printf("SUB %s, R%d\n", quads[i].op2, regCount);
        } else if (quads[i].operator == '+') {
            printf("ADD R%d, R%d\n", regCount - 1, regCount);
        }

        if (i == n - 1) {
            printf("MOV R%d, %s\n", regCount, quads[i].lhs);
        }

        if (quads[i].operator == '-') {
            regCount++;
        }
    }
}

int main() {
    Quadruple quads[] = {
        {"t", "a", '-', "b"},
        {"u", "a", '-', "c"},
        {"v", "t", '+', "u"},
        {"d", "v", '+', "u"}
    };

    int n = sizeof(quads) / sizeof(quads[0]);
    generateCode(quads, n);

    return 0;
}
