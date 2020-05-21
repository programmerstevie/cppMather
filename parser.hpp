#ifndef _PARSER_HPP_
#define _PERSER_HPP_ 1

#include "evaluator.hpp"
#include "includes.hpp"
#include "grammar.hpp"
#include "lexer.hpp"

enum Precedence {
  PARENTHETICAL,
  ADDITIVE,
  MULTIPLICATIVE,
  EXPONENTIAL,
  NEGATIVE
};

Expression *parse(const std::vector<Token*> &tokens);

std::string binOpStr(Operation binOp);

void pushOpExpr (Operation &nextOp, const std::vector<Operation> &OpStack, std::vector<Expression*> &exprStack);
#endif