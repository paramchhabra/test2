#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char result[10];
    char op1[10];
    char oper[2];
    char op2[10];
} Instruction;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void generateTAC(char *expression) {
    Instruction tac[MAX];
    char operands[MAX][10];
    char operators[MAX];
    int topOperands = -1, topOperators = -1, tempCounter = 1, tacIndex = 0;

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        if (isspace(ch)) continue;

        if (isalnum(ch)) { // Operand
            char operand[10];
            sprintf(operand, "%c", ch);
            strcpy(operands[++topOperands], operand);
        } else if (ch == '(') {
            operators[++topOperators] = ch;
        } else if (ch == ')') {
            // Solve all operators until '('
            while (topOperators >= 0 && operators[topOperators] != '(') {
                char op2[10], op1[10], oper[2], temp[10];
                strcpy(op2, operands[topOperands--]);
                strcpy(op1, operands[topOperands--]);
                sprintf(oper, "%c", operators[topOperators--]);
                sprintf(temp, "t%d", tempCounter++);
                strcpy(tac[tacIndex].result, temp);
                strcpy(tac[tacIndex].op1, op1);
                strcpy(tac[tacIndex].oper, oper);
                strcpy(tac[tacIndex].op2, op2);
                tacIndex++;
                strcpy(operands[++topOperands], temp);
            }
            topOperators--; // Pop '('
        } else { // Operator
            while (topOperators >= 0 && precedence(operators[topOperators]) >= precedence(ch)) {
                char op2[10], op1[10], oper[2], temp[10];
                strcpy(op2, operands[topOperands--]);
                strcpy(op1, operands[topOperands--]);
                sprintf(oper, "%c", operators[topOperators--]);
                sprintf(temp, "t%d", tempCounter++);
                strcpy(tac[tacIndex].result, temp);
                strcpy(tac[tacIndex].op1, op1);
                strcpy(tac[tacIndex].oper, oper);
                strcpy(tac[tacIndex].op2, op2);
                tacIndex++;
                strcpy(operands[++topOperands], temp);
            }
            operators[++topOperators] = ch;
        }
    }

    // Solve remaining operators
    while (topOperators >= 0) {
        char op2[10], op1[10], oper[2], temp[10];
        strcpy(op2, operands[topOperands--]);
        strcpy(op1, operands[topOperands--]);
        sprintf(oper, "%c", operators[topOperators--]);
        sprintf(temp, "t%d", tempCounter++);
        strcpy(tac[tacIndex].result, temp);
        strcpy(tac[tacIndex].op1, op1);
        strcpy(tac[tacIndex].oper, oper);
        strcpy(tac[tacIndex].op2, op2);
        tacIndex++;
        strcpy(operands[++topOperands], temp);
    }

    // Output the TAC
    printf("\nThree-Address Code:\n");
    for (int i = 0; i < tacIndex; i++) {
        printf("%s = %s %s %s\n", tac[i].result, tac[i].op1, tac[i].oper, tac[i].op2);
    }
}

int main() {
    char expression[MAX];
    printf("Enter an expression: ");
    fgets(expression, MAX, stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Remove newline

    generateTAC(expression);

    return 0;
}
