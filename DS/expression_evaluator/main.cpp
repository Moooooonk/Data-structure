// main.cpp
#include "ourDeque.h"
#include "evaluator.h"
#include <iostream>

int main() {
    evaluator eval;
    char choice = 'y';

    while (choice == 'y' || choice == 'Y') {
        std::string infix = eval.read_expression();
        std::string postfix = eval.convert_to_postfix(infix);
        double result = eval.evaluate_postfix(postfix);

        std::cout << "Infix expression: " << infix << std::endl;
        std::cout << "Postfix expression: " << postfix << std::endl;
        std::cout << "Evaluation result: " << result << std::endl;

        std::cout << "Would you like to evaluate another expression? (y/n): ";
        std::cin >> choice;
        std::cin.ignore();
    }

    return 0;
}
