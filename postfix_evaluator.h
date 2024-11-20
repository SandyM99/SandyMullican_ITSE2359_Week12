#ifndef POSTFIX_EVALUATOR_H
#define POSTFIX_EVALUATOR_H

#include <string>
#include <stack>
#include <stdexcept>

// Function declarations
int evaluatePostfix(const std::string& expression);
bool isValidPostfix(const std::string& expression);

#endif
