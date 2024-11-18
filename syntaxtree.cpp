#include <iostream>
#include <stack>
#include <string>
#include <set>

using namespace std;

struct Node {
    char value;
    Node* left;
    Node* right;

    Node(char v) : value(v), left(nullptr), right(nullptr) {}
};

void printPostfix(Node* root) {
    if (root == nullptr) return;
    printPostfix(root->left);
    printPostfix(root->right);
    cout << root->value;
}

Node* buildSyntaxTree(string expression) {
    stack<Node*> nodeStack;
    stack<char> opStack;

    auto precedence = [](char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    };

    auto applyOperator = [&nodeStack](char op) {
        Node* right = nodeStack.top(); nodeStack.pop();
        Node* left = nodeStack.top(); nodeStack.pop();
        Node* newNode = new Node(op);
        newNode->left = left;
        newNode->right = right;
        nodeStack.push(newNode);
    };

    for (char ch : expression) {
        if (isalnum(ch)) {
            nodeStack.push(new Node(ch));
        } else if (ch == '(') {
            opStack.push(ch);
        } else if (ch == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                applyOperator(opStack.top());
                opStack.pop();
            }
            opStack.pop();
        } else {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(ch)) {
                applyOperator(opStack.top());
                opStack.pop();
            }
            opStack.push(ch);
        }
    }

    while (!opStack.empty()) {
        applyOperator(opStack.top());
        opStack.pop();
    }

    return nodeStack.top();
}

void collectNodes(Node* root, set<char>& leaves, set<char>& internalNodes) {
    if (root == nullptr) return;
    
    if (root->left == nullptr && root->right == nullptr) {
        leaves.insert(root->value);
    } else {
        internalNodes.insert(root->value);
        collectNodes(root->left, leaves, internalNodes);
        collectNodes(root->right, leaves, internalNodes);
    }
}

int main() {
    string expression = "a*(b+c)-d/2";

    Node* syntaxTreeRoot = buildSyntaxTree(expression);

    set<char> leaves, internalNodes;
    collectNodes(syntaxTreeRoot, leaves, internalNodes);

    cout << "Root Node: " << syntaxTreeRoot->value << endl;

    Node* leftSubTree = syntaxTreeRoot->left;
    Node* rightSubTree = syntaxTreeRoot->right;

    cout << "\nLeft SubTree Internal Node: " << leftSubTree->value << endl;
    cout << "Left Subtree Leave Nodes: " << leftSubTree->left->value << " , "
         << leftSubTree->right->left->value << " , "
         << leftSubTree->right->right->value << endl;

    cout << "\nRight SubTree Internal Node: " << rightSubTree->value << endl;
    cout << "Right Subtree Leave Nodes: " << rightSubTree->left->value << " , "
         << rightSubTree->right->value << endl;

    cout << "\nPOSTFIX NOTATION is ";
    printPostfix(syntaxTreeRoot);
    cout << endl;

    return 0;
}
