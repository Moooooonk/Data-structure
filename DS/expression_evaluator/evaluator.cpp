// evaluator.cpp
#include "evaluator.h"
#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <map>

std::string evaluator::read_expression() {
    std::string expression;
    std::cout << "Enter an infix expression: ";
    std::getline(std::cin, expression);
    return expression;
}

int evaluator::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string evaluator::convert_to_postfix(const std::string& infix) {
    std::stack<char> operators;
    std::stringstream postfix;
    for (char ch : infix) {
        if (std::isspace(ch)) continue;
        if (std::isdigit(ch) || std::isalpha(ch)) {
            postfix << ch << ' ';
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            operators.push(ch);
        }
    }
    while (!operators.empty()) {
        postfix << operators.top() << ' ';
        operators.pop();
    }
    return postfix.str();
}

double evaluator::evaluate_postfix(const std::string& postfix) {
    std::stack<double> operands;
    std::istringstream iss(postfix);
    std::string token;
    std::map<char, double> variables;
    
    while (iss >> token) {
        if (std::isdigit(token[0])) {
            operands.push(std::stod(token));
        } else if (std::isalpha(token[0])) {
            if (variables.find(token[0]) == variables.end()) {
                std::cout << "Enter value for " << token[0] << ": ";
                std::cin >> variables[token[0]];
            }
            operands.push(variables[token[0]]);
        } else {
            double b = operands.top(); operands.pop();
            double a = operands.top(); operands.pop();
            switch (token[0]) {
                case '+': operands.push(a + b); break;
                case '-': operands.push(a - b); break;
                case '*': operands.push(a * b); break;
                case '/': operands.push(a / b); break;
            }
        }
    }
    return operands.top();
}
