#include <stdio.h>
#include <string.h>

#define MAX_VARS 10

// Structure for symbol table entry
typedef struct {
    char name[50];
    char type[10];
    int address;
} Symbol;

int main() {
    Symbol symbolTable[MAX_VARS]; // Symbol table
    int address = 1000;           // Initial memory address
    int count = 0;                // Number of variables

    // Sample declarations
    char declaration1[] = "int a, b;";
    char declaration2[] = "float c;";
    char declaration3[] = "char z;";

    // Function to process variable declaration
    void processDeclaration(char *declaration, char *type) {
        char *token = strtok(declaration, ",; "); // Tokenize the declaration
        // Skip the type token (first token)
        token = strtok(NULL, ",; "); // Move to first variable name

        while (token != NULL) {
            // Insert into symbol table
            strcpy(symbolTable[count].name, token);
            strcpy(symbolTable[count].type, type);
            symbolTable[count].address = address;
            count++;

            // Move address based on type size
            if (strcmp(type, "int") == 0) {
                address += 2; // int takes 2 bytes
            } else if (strcmp(type, "float") == 0) {
                address += 4; // float takes 4 bytes
            } else if (strcmp(type, "char") == 0) {
                address += 1; // char takes 1 byte
            }

            token = strtok(NULL, ",; "); // Get the next token
        }
    }

    // Process declarations
    processDeclaration(declaration1, "int");
    processDeclaration(declaration2, "float");
    processDeclaration(declaration3, "char");

    // Print the symbol table
    printf("Symbol Name\tType\tAddress\n");
    for (int i = 0; i < count; i++) {
        printf("%-15s%-10s%-6d\n", symbolTable[i].name, symbolTable[i].type, symbolTable[i].address);
    }

    return 0;
}
