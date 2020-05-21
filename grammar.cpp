#include "grammar.hpp"

Const_E::Const_E(int value)
{
  this->value = value;
  this->type = CONST_E;
}

BinaryOp_E::BinaryOp_E(Expression* leftExpr, Expression* rightExpr, Operation operation)
{
  this->leftExpr = leftExpr;
  this->rightExpr = rightExpr;
  this->operation = operation;
  this->type = BINARYOP_E;
}


Neg_E::Neg_E(Expression* expression)
{
  this->expression = expression;
  this->type = NEG_E;
}
