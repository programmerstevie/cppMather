#ifndef _EVALUATOR_HPP_
#define _EVALUATOR_HPP_ 1

#include "includes.hpp"
#include "grammar.hpp"

long double evaluate(Expression* expression);

std::string prettyPrint(Expression* expression, bool parens = false);

#endif