#include "evaluator.hpp"

long double evaluate(Expression* expression) {
  long double test_eval, ans;
  switch (expression->getType())
  {
    case CONST_E:
    {
      Const_E *cExpr = (Const_E*) expression;
      ans = cExpr->getValue();
      break;
    }
    case NEG_E:
    {
      Neg_E *nExpr = (Neg_E*) expression;
      ans = -evaluate(nExpr->getExpr());
      break;
    }
    case BINARYOP_E:
    {
      BinaryOp_E *bExpr = (BinaryOp_E*) expression;
      Expression *lExpr = bExpr->getLeftExpr(), *rExpr = bExpr->getRightExpr();
      switch(bExpr->getOperation()) {
        case ADD:
          ans = evaluate(lExpr) + evaluate(rExpr);
          break;
        case SUB:
          ans = evaluate(lExpr) - evaluate(rExpr);
          break;
        case MUL:
          ans = evaluate(lExpr) * evaluate(rExpr);
          break;
        case DIV:
          test_eval = evaluate(rExpr);
          if (test_eval == 0) {
            std::cerr << "[EVAL ERROR] : DIVISION BY ZERO [ " << prettyPrint(expression, false) << " ]" << std::endl;
            exit(EXIT_FAILURE);
          }
          ans = evaluate(lExpr) / test_eval;
          break;
        case EXP:
          ans = std::pow(evaluate(lExpr), evaluate(rExpr));
          break;
        case MOD:
          ans = std::fmod(evaluate(lExpr), evaluate(rExpr));
          break;
        default:
          std::cerr << "Unexpected binary operation! Are you trying to use NEG as an infix operator?" << std::endl;
          exit(EXIT_FAILURE);
          break;
      }
      break;
    }
    default:
    {
      std::cerr << "Unexpected expression type! Are you trying to evaluate an expression with no type?" << std::endl;
      exit(EXIT_FAILURE);
      break;
    }
  }
  delete expression;
  //std::cout << "del expr" << std::endl;
  return ans;
}

std::string prettyPrint(Expression* expression, bool parens)
{
  std::string lparen = "", rparen = "";
  if (parens) {
    lparen = "(";
    rparen = ")";
  }
  switch (expression->getType())
  {
    case CONST_E:
    {
      Const_E *cExpr = (Const_E*) expression;
      return std::to_string(cExpr->getValue());
      break;
    }
    case NEG_E:
    {
      Neg_E *nExpr = (Neg_E*) expression;
      return lparen + "-" + prettyPrint(nExpr->getExpr(), true) + rparen;
      break;
    }
    case BINARYOP_E:
    {
      BinaryOp_E *bExpr = (BinaryOp_E*) expression;
      Expression *lExpr = bExpr->getLeftExpr(), *rExpr = bExpr->getRightExpr();
      switch(bExpr->getOperation()) {
        case ADD:
          return lparen + prettyPrint(lExpr, true) + " + " +  prettyPrint(rExpr, true) + rparen;
          break;
        case SUB:
          return lparen + prettyPrint(lExpr, true) + " - " +  prettyPrint(rExpr, true) + rparen;
          break;
        case MUL:
          return lparen + prettyPrint(lExpr, true) + " * " +  prettyPrint(rExpr, true) + rparen;
          break;
        case DIV:
          return lparen + prettyPrint(lExpr, true) + " / " +  prettyPrint(rExpr, true) + rparen;
          break;
        case EXP:
          return lparen + prettyPrint(lExpr, true) + " ^ " +  prettyPrint(rExpr, true) + rparen;
          break;
        case MOD:
          return lparen + prettyPrint(lExpr, true) + " % " +  prettyPrint(rExpr, true) + rparen;
          break;
        default:
          std::cerr << "Unexpected binary operation! Are you trying to print NEG as an infix operator?" << std::endl;
          exit(EXIT_FAILURE);
          break;
      }
      break;
    }
    default:
    {
      std::cerr << "Unexpected expression type! Are you trying to print an expression with no type?" << std::endl;
      exit(EXIT_FAILURE);
      break;
    }
  }
  std::cerr << "PRETTYPRINT ERROR" << std::endl;
  exit(EXIT_FAILURE);
}