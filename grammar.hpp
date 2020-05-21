#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_ 1

#include "includes.hpp"
#include "token.hpp"

enum ExpressionType {
  CONST_E,
  BINARYOP_E,
  NEG_E
};

class Expression {
  public:
    virtual inline ExpressionType getType() { return this->type; }
  protected:
    ExpressionType type;
};

class Const_E: public Expression {
  public:
    Const_E(int value);
    inline int getValue() { return this->value; }
  private:
    int value;
};

class BinaryOp_E: public Expression {
  public:
    BinaryOp_E(Expression* leftExpr, Expression* rightExpr, Operation operation);
    inline Expression* getLeftExpr() { return this->leftExpr; }
    inline Expression* getRightExpr() { return this->rightExpr; }
    inline Operation getOperation() { return this->operation; }
  private:
    Operation operation;
    Expression* leftExpr;
    Expression* rightExpr;
};

class Neg_E: public Expression {
  public:
    Neg_E(Expression* expression);
    inline Expression* getExpr() { return this->expression; };
  private:
    Expression* expression;
};

#endif