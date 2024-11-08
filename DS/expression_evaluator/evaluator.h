// evaluator.h
#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>

class evaluator {
public:
    std::string read_expression();
    std::string convert_to_postfix(const std::string& infix);
    double evaluate_postfix(const std::string& postfix);

private:
    int precedence(char op);
};

#endif
