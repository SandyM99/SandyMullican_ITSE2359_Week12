#include "postfix_evaluator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> history;
    std::string expression;

    while (true) {
        std::cout << "\nEnter a postfix expression (or type 'exit' to quit): ";
        std::getline(std::cin, expression);

        if (expression == "exit") break;

        try {
            if (!isValidPostfix(expression)) {
                throw std::invalid_argument("Invalid expression format.");
            }

            int result = evaluatePostfix(expression);
            std::cout << "Result: " << result << std::endl;

            history.push_back(expression + " = " + std::to_string(result));

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    // Save the history of evaluated expressions to a file
    std::ofstream historyFile("postfix_history.txt");
    if (historyFile.is_open()) {
        for (const std::string& record : history) {
            historyFile << record << std::endl;
        }
        historyFile.close();
        std::cout << "History saved to 'postfix_history.txt'." << std::endl;
    } else {
        std::cout << "Error: Could not save history to file." << std::endl;
    }

    if (!history.empty()) {
        std::cout << "\nHistory of Expressions and Results:" << std::endl;
        for (const std::string& record : history) {
            std::cout << record << std::endl;
        }
    }

    return 0;
}
