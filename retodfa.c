#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STATES 100
#define MAX_CHAR 128
typedef struct
{
    int transitions[MAX_STATES][MAX_CHAR];
    int is_final[MAX_STATES];
    int start_state;
    int num_states;
} DFA;
DFA create_complex_dfa()
{
    DFA dfa;
    dfa.num_states = 5;
    dfa.start_state = 0;
    memset(dfa.transitions, -1, sizeof(dfa.transitions));
    memset(dfa.is_final, 0, sizeof(dfa.is_final));
    dfa.transitions[0]['a'] = 1;
    dfa.transitions[1]['a'] = 2;
    dfa.transitions[1]['b'] = 1;
    dfa.transitions[2]['a'] = 3;
    dfa.transitions[2]['b'] = 4;
    dfa.transitions[3]['a'] = 3;
    dfa.transitions[3]['b'] = 4;
    dfa.transitions[4]['a'] = 1;
    dfa.is_final[0] = 1;
    dfa.is_final[1] = 1;
    dfa.is_final[4] = 1;
    return dfa;
}
int simulate_dfa(DFA *dfa, const char *input)
{
    int current_state = dfa->start_state;
    for (int i = 0; i < strlen(input); i++)
    {
        current_state = dfa->transitions[current_state][(int)input[i]];
        if (current_state == -1)
            return 0;
    }
    return dfa->is_final[current_state];
}
int main()
{
    DFA dfa = create_complex_dfa();
    char input[100];
    printf("Enter input string: ");
    scanf("%s", input);
    printf("Input '%s' is %s by the DFA.\n", input, simulate_dfa(&dfa, input) ? "accepted" : "rejected");
    return 0;
}
