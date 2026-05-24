//`cpp DSA Assignment Expression Evaluator
#include<iostream>
#include<string>
#include<stack>
#include<map>
#include<vector>
#include<set>
#include<cctype>
#include<cstdlib>
using namespace std;

bool isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isOpeningBracket(char ch)
{
    return ch == '(' || ch == '[' || ch == '{';
}

bool isClosingBracket(char ch)
{
    return ch == ')' || ch == ']' || ch == '}';
}

bool matchingBrackets(char open, char close)
{
    return  (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}');
}

int precedence(char op) // Fixed typo here (was precendence)
{
    if (op == '*' || op == '/')
    {
        return 2;
    }
    if (op == '+' || op == '-')
    {
        return 1;
    }
    return 0;
}

bool isVariable(string s)
{
    if (s.empty())
    {
        return false;
    }
    if (!(isalpha(s[0])) || s[0] == '_')
    {
        return false;
    }
    for (int i = 1;i < s.size();i++)
    {
        if (!(isalnum(s[i]) || s[i] == '_'))
        {
            return false;
        }
    }
    return true;
}

bool isNumber(string s)
{
    if (s.empty())
    {
        return false;
    }
    for (char ch : s)
    {
        if (!isdigit(ch))
        {
            return false; // Fixed typo here (was retrun)
        }
    }
    return true;
}

vector<string> tokenize(string expression)
{
    vector<string> tokens;
    for (int i = 0;i < expression.size();)
    {
        if (expression[i] == ' ') // Fixed syntax error here
        {
            i++;
        }
        else if (isdigit(expression[i]))
        {
            string number;

            while (i < expression.size() && isdigit(expression[i]))
            {
                number += expression[i];
                i++;
            }

            tokens.push_back(number);
        }
        else if (isalpha(expression[i]) || expression[i] == '_')
        {
            string variable;

            while (i < expression.size() &&
                (isalnum(expression[i]) || expression[i] == '_'))
            {
                variable += expression[i];
                i++;
            }

            tokens.push_back(variable);
        }

        else if (isOperator(expression[i]) ||
            isOpeningBracket(expression[i]) ||
            isClosingBracket(expression[i]))
        {
            tokens.push_back(string(1, expression[i]));
            i++;
        }

        else
        {
            cerr << "Syntax Error" << endl;
            exit(1);
        }
    }
    return tokens;
}

bool validateSyntax(vector<string>& tokens)
{
    if (tokens.empty())
    {
        return false;
    }

    stack<char> brackets;

    for (int i = 0; i < tokens.size(); i++)
    {
        string token = tokens[i];

        if (token.size() == 1 && isOpeningBracket(token[0]))
        {
            brackets.push(token[0]);
        }
        else if (token.size() == 1 && isClosingBracket(token[0]))
        {
            if (brackets.empty())
            {
                return false;
            }

            if (!matchingBrackets(brackets.top(), token[0])) // Fixed typo here (added 's')
            {
                return false;
            }

            brackets.pop();
        }
    }

    if (!brackets.empty())
    {
        return false;
    }

    return true;
}

vector <string> infixToPostfix(vector<string>& tokens) // Fixed typo here (capital T)
{
    vector<string> postfix;
    stack<string> st;
    for (string token : tokens)
    {
        if (isNumber(token) || isVariable(token))
        {
            postfix.push_back(token);
        }

        else if (token.size() == 1 && isOpeningBracket(token[0]))
        {
            st.push(token);
        }

        else if (token.size() == 1 && isClosingBracket(token[0]))
        {
            while (!st.empty() &&
                !isOpeningBracket(st.top()[0]))
            {
                postfix.push_back(st.top());
                st.pop();
            }

            st.pop();
        }
        else if (token.size() == 1 && isOperator(token[0]))
        {
            while (!st.empty() &&
                precedence(st.top()[0]) >= precedence(token[0]))
            {
                postfix.push_back(st.top());
                st.pop();
            }

            st.push(token);
        }
    }
    while (!st.empty())
    {
        postfix.push_back(st.top());
        st.pop();
    }
    return postfix;
}

int evaluatePostfix(vector<string>& postfix,
    map<string, int>& values)
{
    stack<int> st;

    for (string token : postfix)
    {
        if (isNumber(token))
        {
            st.push(stoi(token));
        }

        else if (isVariable(token))
        {
            st.push(values[token]);
        }

        else if (token.size() == 1 && isOperator(token[0]))
        {
            if (st.size() < 2)
            {
                cerr << "Logical Error" << endl;
                exit(3);
            }

            int right = st.top();
            st.pop();

            int left = st.top();
            st.pop();

            int result;

            if (token[0] == '+')
            {
                result = left + right;
            }

            else if (token[0] == '-')
            {
                result = left - right;
            }

            else if (token[0] == '*')
            {
                result = left * right;
            }

            else
            {
                if (right == 0)
                {
                    cerr << "Runtime Error" << endl;
                    exit(2);
                }

                result = left / right;
            }

            st.push(result);
        }
    }

    if (st.size() != 1)
    {
        cerr << "Logical Error" << endl;
        exit(3);
    }

    return st.top();
}

int main()
{
    string expression;

    getline(cin, expression);

    vector<string> tokens = tokenize(expression);

    if (!validateSyntax(tokens))
    {
        cerr << "Syntax Error" << endl;
        return 1;
    }

    vector<string> postfix = infixToPostfix(tokens);

    for (string token : postfix)
    {
        cerr << token << " ";
    }

    cerr << endl;

    set<string> variables;

    for (string token : tokens)
    {
        if (isVariable(token))
        {
            variables.insert(token);
        }
    }

    map<string, int> values;

    for (string var : variables)
    {
        cerr << "Enter value for " << var << ": ";

        cin >> values[var];
    }

    int answer = evaluatePostfix(postfix, values);

    cout << answer << endl;

    return 0;
}