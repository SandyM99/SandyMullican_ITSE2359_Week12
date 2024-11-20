#include "postfix_evaluator.h"
#include <sstream>
#include <cmath>

int evaluatePostfix(const std::string& expression) {
    std::stack<int> s;
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            s.push(std::stoi(token));
        } else if (token.size() == 1 && std::string("+-*/%^").find(token[0]) != std::string::npos) {
            if (s.size() < 2) {
                throw std::invalid_argument("Invalid expression: insufficient operands.");
            }
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();

            switch (token[0]) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/':
                    if (b == 0) throw std::runtime_error("Division by zero.");
                    s.push(a / b); break;
                case '%':
                    if (b == 0) throw std::runtime_error("Modulo by zero.");
                    s.push(a % b); break;
                case '^': s.push(std::pow(a, b)); break;
                default: throw std::invalid_argument("Invalid operator.");
            }
        } else {
            throw std::invalid_argument("Invalid character in expression.");
        }
    }

    if (s.size() != 1) {
        throw std::invalid_argument("Invalid expression: too many operands or operators.");
    }

    return s.top();
}

bool isValidPostfix(const std::string& expression) {
    int operandCount = 0, operatorCount = 0;
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            operandCount++;
        } else if (token.size() == 1 && std::string("+-*/%^").find(token[0]) != std::string::npos) {
            operatorCount++;
            if (operandCount < 2) return false;
            operandCount--;
        } else {
            return false;
        }
    }

    return operandCount == 1 && operatorCount > 0;
}

