#include "token.hpp"

Token::Token()
{
  this->token = "";
}
Token::Token(std::string token)
{
  this->token = token;
}
std::string Token::getToken() {
  return this->token;
}

IntToken::IntToken(std::string token):Token(token)
{
  if (token.find_first_not_of("0123456789") != std::string::npos) {
    std::cerr << "Token > " << token << " < is not an IntToken" << std::endl;
    exit(EXIT_FAILURE);
  }
  this->value = stoi(token);
}

int IntToken::getVal()
{
  return this->value;
}


ParenToken::ParenToken(std::string token):Token(token)
{
  if (token != "(" && token != ")") {
    std::cerr << "Token > " << token << " < is not a ParenToken" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (token == "(")
    this->side = LEFT;
  else
    this->side = RIGHT;
}

ParenSide ParenToken::getSide()
{
  return this->side;
}


BinaryOpToken::BinaryOpToken(std::string token):Token(token)
{
  std::vector<std::string> ops = {"+", "-", "*", "/", "^", "%"};
  if (std::find(ops.begin(), ops.end(), token) == ops.end()) {
    std::cerr << "Token > " << token << " < is not a BinaryOpToken" << std::endl;
    exit(EXIT_FAILURE);
  }
  switch (token[0]) {
    case '+':
      this->operation = ADD;
      break;
    case '*':
      this->operation = MUL;
      break;
    case '-':
      this->operation = SUB;
      break;
    case '/':
      this->operation = DIV;
      break;
    case '%':
      this->operation = MOD;
      break;
    case '^':
      this->operation = EXP;
      break;
  }
}
Operation BinaryOpToken::getBinOp()
{
  return this->operation;
}