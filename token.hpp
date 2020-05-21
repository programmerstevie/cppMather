#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_ 1

#include "includes.hpp"

enum Operation {
  ADD,
  SUB,
  MUL,
  DIV,
  EXP,
  MOD,
  NEG, // THIS IS NOT TO BE USED FOR A TOKEN
  PAR  // THIS IS NOT TO BE USED FOR A TOKEN
};

enum TokenType {
  INT_T,
  BINOP_T,
  PAREN_T
};

enum ParenSide {
  LEFT,
  RIGHT
};

class Token {
  public:
    Token();
    Token(std::string token);
    virtual std::string getToken();
    virtual TokenType getType() = 0;
  protected:
    std::string token;
};

class IntToken: public Token {
  public:
    IntToken(std::string token);
    int getVal();
    inline TokenType getType() { return INT_T; }
  private:
    int value;
};

class ParenToken: public Token {
  public:
    ParenToken(std::string token);
    ParenSide getSide();
    inline TokenType getType() { return PAREN_T; }
  private:
    ParenSide side;
};

class BinaryOpToken: public Token {
  public:
    BinaryOpToken(std::string token);
    Operation getBinOp();
    inline TokenType getType() { return BINOP_T; }
  private:
    Operation operation;
};
#endif