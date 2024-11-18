    #include <iostream>
    #include <fstream>
    #include <string>
    #include <cctype>

    using namespace std;
    bool isKeyword(string token)
    {
        static const string keywords[] =
            {"float", "int", "char", "double", "void", "return", "if", "else", "for", "while"};
        for (const string &keyword : keywords)
        {
            if (token == keyword)
            {
                return true;
            }
        }
        return false;
    }
    bool isIdentifier(string token)
    {
        if (token.empty() || !isalpha(token[0]))
        {
            return false;
        }
        for (char c : token)
        {
            if (!isalnum(c) && c != '_')
            {
                return false;
            }
        }
        return true;
    }
    bool isOperator(char ch)
    {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
                ch == '<' || ch == '>');
    }
    void lex_analysis(string input)
    {
        int n = input.length();
        int i = 0;
        while (i < n)
        {
            char ch = input[i];
            if (isspace(ch))
            {
                i++;
                continue;
            }
            if (isalpha(ch))
            {
                string token;
                while (isalnum(ch) || ch == '_')
                {
                    token += ch;
                    i++;
                    if (i >= n)
                    {
                        break;
                    }
                    ch = input[i];
                }
                if (isKeyword(token))
                {
                    cout << "Keyword: " << token << endl;
                }
                else if (isIdentifier(token))
                {
                    cout << "Identifier: " << token << endl;
                }
                else
                {
                    cout << "Unknown: " << token << endl;
                }
            }
            else if (isOperator(ch))
            {
                cout << "Operator: " << ch << endl;
                i++;
            }
            else
            {
                cout << "Unknown: " << ch << endl;
                i++;
            }
        }
    }
    int main()
    {
        ifstream inputFile("input.txt");
        if (!inputFile.is_open())
        {
            cout << "Error opening the input file." << endl;
            return 1;
        }
        string input;
        getline(inputFile, input);
        lex_analysis(input);
        inputFile.close();
        return 0;
    }