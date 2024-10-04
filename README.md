# C++ Expression Parser and Evaluator

This project is a C++ implementation of a mathematical expression parser and evaluator. It takes an input string representing a mathematical expression, tokenizes it, parses it into an Abstract Syntax Tree (AST), and then evaluates the result. The parser supports basic arithmetic operations such as addition, subtraction, multiplication, division, exponentiation, and modulus, along with parentheses for grouping and unary negation. This could easily be extended to support common functions such as sine and cosine.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Contributing](#contributing)
- [License](#license)

## Features

- Parses mathematical expressions into an Abstract Syntax Tree (AST)
- Supports basic arithmetic operations: `+`, `-`, `*`, `/`, `%`, `^`
- Handles unary negation and parentheses for grouping
- Error handling for syntax errors like unmatched parentheses or division by zero
- Clean, modular design with a lexer, parser, and evaluator

## Getting Started

### Prerequisites

To build and run this project, you will need:
- A C++ compiler supporting C++11 or later (e.g., GCC, Clang)
- `make` (optional, if you use a Makefile)
- Git (to clone the repository)

### Installing

1. **Clone the repository:**

   ```bash
   git clone https://github.com/programmerstevie/cppMather.git
   cd cppMather
   ```

2. **Compile the project:**

   If you're using `make`, simply run:

   ```bash
   make
   ```

   Alternatively, compile the source files manually:

   ```bash
   g++ -std=c++11 -o parser main.cpp lexer.cpp parser.cpp evaluator.cpp
   ```

## Usage

After compiling the project, run the executable and enter a mathematical expression to evaluate:

1. **Run the executable:**

   ```bash
   ./parser
   ```

2. **Input a mathematical expression:**

   For example:

   ```bash
   (5 + 3) * 2 - 4 ^ 2
   ```

3. **The program will output:**

   ```bash
   (5 + 3) * 2 - 4 ^ 2 = -4
   ```

## Project Structure

- **`includes.hpp`**: Centralized file for including necessary standard library headers.
- **`lexer.hpp` / `lexer.cpp`**: Responsible for tokenizing the input string into meaningful tokens (numbers, operators, parentheses).
- **`parser.hpp` / `parser.cpp`**: Processes tokens into an Abstract Syntax Tree (AST) using operator precedence and associativity rules.
- **`evaluator.hpp` / `evaluator.cpp`**: Evaluates the AST and computes the result of the expression.
- **`token.hpp` / `token.cpp`**: Defines the different types of tokens used in the program (integer tokens, operator tokens, parenthesis tokens).
- **`main.cpp`**: The entry point of the program, showing an example of how to go from an expression string to its evaluation.

## How It Works

### 1. Lexical Analysis (Tokenization)

The lexer (`lexer.cpp`) breaks down the input string into **tokens** representing integers, operators, and parentheses. For example, the expression `3 + (5 * 2)` would be tokenized into:

- `IntToken(3)`
- `BinaryOpToken(+)`
- `ParenToken(()`
- `IntToken(5)`
- `BinaryOpToken(*)`
- `IntToken(2)`
- `ParenToken())`

### 2. Parsing

The parser (`parser.cpp`) uses a **shunting yard algorithm** to convert the tokens into an Abstract Syntax Tree (AST). It ensures that operations are applied in the correct order by respecting operator precedence and associativity.

For example, for the input `5 + 3 * 2`, the AST will look like this:

```
     +
   /   \
  5     *
       / \
      3   2
```

### 3. Evaluation

The evaluator (`evaluator.cpp`) recursively evaluates the AST to compute the final result of the expression. For example, the AST for `5 + 3 * 2` will be evaluated as:

1. Multiply `3 * 2` to get `6`.
2. Add `5 + 6` to get `11`.

### Error Handling

The parser and evaluator have several built-in error checks to ensure that the input expression is valid:
- **Unmatched Parentheses**: The parser checks for balanced parentheses.
- **Division by Zero**: The evaluator checks for division by zero and terminates with an error if encountered.
- **Invalid Tokens**: The lexer and token constructors validate that only valid tokens are processed.

### Pretty Printing

The `prettyPrint()` function in `evaluator.cpp` can convert an AST back into a human-readable string, showing the expression in standard infix notation.

## Contributing

Contributions are welcome! If you have suggestions or improvements, feel free to fork the repository and submit a pull request.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a pull request

## License

Distributed under the MIT License. See `LICENSE` for more information.
