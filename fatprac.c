#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct
{
    char op;
    int value;
    Node *left;
    Node *right;
} Node;

Node nodes[10];

void create_list(char statement[], int n)
{
    for (int i = 0; i < n; i++)
    {
        nodes[i].left = NULL;
        nodes[i].right = NULL;
        nodes[i].op = NULL;
        nodes[i].value = NULL;

        if (isdigit(statement[i]))
        {
            nodes[i].value = atoi(statement[i]);
        }
        else
        {
            nodes[i].op = statement[i];
        }
    }
}

void parsetree(int n)
{
    int n = n;
    int divop = 0;
    int mulop = 0;
    int subop = 0;
    int addop = 0;

    for (int i = 0; i < n; i++)
    {
        switch (nodes[i].op)
        {
        case '/':
            divop++;
            break;
        case '*':
            mulop++;
            break;
        case '+':
            addop++;
            break;
        case '-':
            subop++;
            break;
        default:
            break;
        }
    }

    while (divop != 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (nodes[i] == '/')
            {
                nodes[i].value = nodes[i-1].value/nodes[i+1].value;
                nodes[i].left = nodes[i-1];
                nodes[i].right = nodes[i+1];
                nodes[i-1] = -1;
                nodes[i+1] = -1;
            }
        }
    }
    while (mulop != 0)
    {
        /* code */
    }
    while (addop != 0)
    {
        /* code */
    }
    while (subop != 0)
    {
        /* code */
    }
}
