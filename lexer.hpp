#ifndef _LEXER_HPP_
#define _LEXER_HPP_ 1

#include "includes.hpp"
#include "token.hpp"

void whitespaceT(std::string &msg);
bool integerT(Token *&token, std::string &msg);
bool parenT(Token *&token, std::string &msg);
bool binaryOpT(Token *&token, std::string &msg);
Token* getToken(std::string &msg);
std::vector<Token*> tokenize(const std::string& msg);
#endif