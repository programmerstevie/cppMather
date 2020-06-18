#include "parser.hpp"

Expression *parse(const std::vector<Token*>& tokens)
{
  std::vector<Expression*> exprStack;
  std::vector<Operation> opStack;
  Operation operation, nextOp;
  int opSize;

  std::unordered_map<Operation, Precedence> precedences ({
    {PAR, PARENTHETICAL},
    {ADD, ADDITIVE},
    {SUB, ADDITIVE},
    {MUL, MULTIPLICATIVE},
    {DIV, MULTIPLICATIVE},
    {MOD, MULTIPLICATIVE},
    {EXP, EXPONENTIAL},
    {NEG, NEGATIVE}
  });

  std::unordered_map<Operation, int> args ({
    {PAR, 0},
    {ADD, 1},
    {SUB, 1},
    {MUL, 1},
    {DIV, 1},
    {MOD, 1},
    {EXP, 1},
    {NEG, 0}
  });


  for (Token* token : tokens) {
    switch (token->getType()) {
      case INT_T:
      {
        IntToken *itoken = (IntToken*) token;
        exprStack.push_back(new Const_E(itoken->getVal()));
        //std::cout << "new constExpr" << std::endl;
        break;
      }
      case PAREN_T:
      {
        ParenToken *ptoken = (ParenToken*) token;
        if (ptoken->getSide() == LEFT) {
          opStack.push_back(PAR);
          break;
        }

        // RIGHT PARENTHESES
        if (opStack.empty()) {
          std::cerr << "[SYNTAX ERROR] : UNMATCHED RIGHT PARENTHESIS" << std::endl;
          exit(EXIT_FAILURE);
        }

        // LOOP TO FIND RIGHT PARENTHESES
        nextOp = opStack.back();
        opStack.pop_back();
        while (nextOp != PAR) {
          pushOpExpr(nextOp, opStack, exprStack);
          
          if (opStack.empty()) {
            std::cerr << "[SYNTAX ERROR] : UNMATCHED RIGHT PARENTHESIS" << std::endl;
            exit(EXIT_FAILURE);
          }
          nextOp = opStack.back();
          opStack.pop_back();
        }
        break;
      }
      case BINOP_T:
      {
        BinaryOpToken *btoken = (BinaryOpToken*) token;
        operation = btoken->getBinOp();

        // LEADING NEGATIVE SIGN
        if (opStack.empty()) {
          if (operation == SUB && exprStack.empty()) {
            opStack.push_back(NEG);
          } else {
            opStack.push_back(operation);
          }
          break;
        }

        // PUT OPERATION ONTO OPSTACK
        nextOp = opStack.back();
        while (precedences[nextOp] >= precedences[operation]) {
          opSize = 0;
          for (Operation op : opStack)
            opSize += args[op];
          if (exprStack.size() <= opSize) {
            if (operation == SUB) {
              operation = NEG;
              break;
            }
            std::cerr << "[SYNTAX ERROR] : CANNOT USE TOKEN > " << token->getToken() << " < AS A PREFIX OPERATION" << std::endl;
            exit(EXIT_FAILURE);
          }
          opStack.pop_back();

          pushOpExpr(nextOp, opStack, exprStack);
          if (opStack.empty())
            break;
          nextOp = opStack.back();
        }
        //std::cout << "pushing..." << binOpStack.size() << std::endl;
        opStack.push_back(operation);
        break;
      }
      default:
      {
        std::cerr << "[SYNTAX ERROR] : UNRECOGNIZED TOKEN > " << token->getToken() << " <" << std::endl;
        exit(EXIT_FAILURE);
        break;
      }
    }
    delete token;
    //std::cout << "del token" << std::endl;
  }

  // FLUSH THE OPSTACK
  while (!opStack.empty()) {
    //std::cout << "loop " << OpStack.size() << std::endl;
    operation = opStack.back();
    opStack.pop_back();

    pushOpExpr(operation, opStack, exprStack);
  }

  // make sure the parser worked
  if (exprStack.size() != 1) {
    std::cerr << "[PARSING ERROR] : UNEXPECTED MULTIPLE SYNTAX TREES: " << exprStack.size() << std::endl;
    Expression* e;
    while (!exprStack.empty()) {
      e = exprStack.back();
      exprStack.pop_back();
      std::cerr << "Tree: " << prettyPrint(e) << std::endl;
    }
    exit(EXIT_FAILURE);
  }

  return exprStack.back();
}

std::string binOpStr(Operation binOp)
{
  switch (binOp) {
    case ADD:
      return "+";
    case SUB:
      return "-";
    case MUL:
      return "*";
    case DIV:
      return "/";
    case EXP:
      return "^";
    case MOD:
      return "%";
    case NEG:
      return "(-)";
    default:
      std::cerr << "Cannot convert binary operation " << binOp << " to string!" << std::endl;
      exit(EXIT_FAILURE);
  }
}

void pushOpExpr (Operation &operation, const std::vector<Operation> &opStack, std::vector<Expression*> &exprStack) {
  Expression *lExpr, *rExpr;
  if (operation == NEG) {
    if (exprStack.size() < 1) {
      std::cerr << "[SYNTAX ERROR] : NO EXPRESSION BOUND TO NEGATIVE SIGN" << std::endl;
      exit(EXIT_FAILURE);
    }
    lExpr = exprStack.back();
    exprStack.pop_back();
    exprStack.push_back(new Neg_E(lExpr));
    //std::cout << "new negExpr" << std::endl;
    return;
  }

  if (exprStack.size() < 2) {
    std::cerr << "[SYNTAX ERROR] : CANNOT USE TOKEN > " << binOpStr(operation) << " < AS A PREFIX OPERATION" << std::endl;
    exit(EXIT_FAILURE);
  }

  rExpr = exprStack.back();
  exprStack.pop_back();
  lExpr = exprStack.back();
  exprStack.pop_back();
  exprStack.push_back(new BinaryOp_E(lExpr, rExpr, operation));
  //std::cout << "new binOpExpr" << std::endl;
}