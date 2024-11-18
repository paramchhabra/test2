#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <stack>

using namespace std;

struct Instruction {
    string result;
    string op1;
    string oper;
    string op2;
};

// Function to check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to generate three-address code
vector<Instruction> generateTAC(string expression) {
    vector<Instruction> tac;
    stack<string> operands;  // To store operands or temporary variables
    stack<char> operators;   // To store operators
    int tempCounter = 1;     // Counter for temporary variables (t1, t2, ...)

    // Parse the expression
    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isspace(ch)) continue;

        if (isalnum(ch)) { // Operand
            string operand(1, ch);
            operands.push(operand);
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            // Solve entire parenthesis
            while (!operators.empty() && operators.top() != '(') {
                string op2 = operands.top(); operands.pop();
                string op1 = operands.top(); operands.pop();
                char oper = operators.top(); operators.pop();
                string temp = "t" + to_string(tempCounter++);
                tac.push_back({temp, op1, string(1, oper), op2});
                operands.push(temp);
            }
            operators.pop(); // Pop '('
        } else { // Operator
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                string op2 = operands.top(); operands.pop();
                string op1 = operands.top(); operands.pop();
                char oper = operators.top(); operators.pop();
                string temp = "t" + to_string(tempCounter++);
                tac.push_back({temp, op1, string(1, oper), op2});
                operands.push(temp);
            }
            operators.push(ch);
        }
    }

    // Solve remaining operators
    while (!operators.empty()) {
        string op2 = operands.top(); operands.pop();
        string op1 = operands.top(); operands.pop();
        char oper = operators.top(); operators.pop();
        string temp = "t" + to_string(tempCounter++);
        tac.push_back({temp, op1, string(1, oper), op2});
        operands.push(temp);
    }

    return tac;
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);

    vector<Instruction> tac = generateTAC(expression);

    cout << "\nThree-Address Code:\n";
    for (const auto &inst : tac) {
        cout << inst.result << " = " << inst.op1;
        if (!inst.oper.empty()) cout << " " << inst.oper << " " << inst.op2;
        cout << endl;
    }

    return 0;
}
