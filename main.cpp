#include "includes.hpp"
#include "lexer.hpp"
#include "evaluator.hpp"
#include "parser.hpp"

long double evalStr(std::string msg) {
  return evaluate(parse(tokenize(msg)));
}

int main(int argc, char* argv[])
{
  std::string msg;
  getline(std::cin, msg);

  std::cout << msg << " = " << evalStr(msg) << std::endl;
  system("pause");
  return 0;
}