#include "lexer.hpp"

void whitespaceT(std::string &msg)
{
  int i = 0;
  char c = msg[0];
  while (isspace(c)) {
    c = msg[++i];
  }
  msg.erase(0, i);
}

bool integerT(Token *&token, std::string &msg)
{
  std::string temp_str = "";
  int i = 0;
  char c = msg[0];
  while (isdigit(c)) {
    temp_str += c;
    c = msg[++i];
  }
  if (i > 0) {
    msg.erase(0, i);
    token = new IntToken(temp_str);
    //std::cout << "new int" << std::endl;
    return true;
  }
  return false;
}

bool parenT(Token *&token, std::string &msg)
{
  char c = msg[0];
  if (c == '(' || c == ')') {
    msg.erase(0, 1);
    token = new ParenToken({c});
    //std::cout << "new paren" << std::endl;
    return true;
  }
  return false;
}

bool binaryOpT(Token *&token, std::string &msg)
{
  char c = msg[0];
  std::vector<char> ops = {'+', '-', '*', '/', '^', '%'};
  if (std::find(ops.begin(), ops.end(), c) != ops.end()) {
    token = new BinaryOpToken({c});
    //std::cout << "new binop" << std::endl;
    msg.erase(0, 1);
    return true;
  }
  return false;
}

Token* getToken(std::string &msg)
{
  Token* token;
  whitespaceT(msg);
  if (integerT(token, msg))
    goto tokenized;
  if (parenT(token, msg))
    goto tokenized;
  if (binaryOpT(token, msg))
    goto tokenized;
  printf("Could not tokenize char > %c < \n", msg[0]);
  exit(EXIT_FAILURE);
tokenized:
  whitespaceT(msg);
  return token;
}

std::vector<Token*> tokenize(const std::string& msg)
{
  std::string temp_string = msg;
  
  std::vector<Token*> tokens = {};
  while (!temp_string.empty()) {
    tokens.push_back(getToken(temp_string));
  }
  return tokens;
}