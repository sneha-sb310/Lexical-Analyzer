# Lexical-Analyzer

## Description

This project implements a **Lexical Analyzer (Lexer)** — the first phase of a compiler — written in C.
A lexical analyzer reads a source code file character by character and breaks it down into meaningful 
units called **tokens**. Each token is classified into a category such as keyword, operator, identifier, 
constant, or special character.

This lexer is designed to tokenize **C language source files**.

---

## Token Types Supported

| Token Type        | Examples                                      |
|-------------------|-----------------------------------------------|
| KEYWORD           | `int`, `float`, `if`, `while`, `return`       |
| IDENTIFIER        | `speed`, `main`, `init_config`                |
| CONSTANT          | `0`, `100`, `1234`                            |
| OPERATOR          | `+`, `-`, `*`, `=`, `!`, `<`, `>`            |
| SPECIAL_CHARACTER | `,`, `;`, `{`, `}`, `(`, `)`, `[`, `]`       |

---

## Keywords Supported (31)

`char` `double` `enum` `float` `int` `long` `short` `signed` `union` `unsigned` `void`
`break` `case` `continue` `default` `do` `else` `for` `goto` `if` `switch` `while`
`auto` `extern` `register` `static` `const` `sizeof` `typedef` `volatile` `return`

---

## How to Run

### Prerequisites
- GCC compiler installed
- A C source file to analyze

### Steps

**1. Clone or download the project files into a folder**

**2. Compile**
```bash
gcc main.c lexer.c -o lexer
```

**3. Run — pass any C source file as argument**
```bash
./lexer test.c
```

**On Windows:**
```bash
gcc main.c lexer.c -o lexer.exe
lexer.exe test.c
```

---
## How It Works

1. `initializeLexer()` opens the input source file
2. `getNextToken()` reads one character at a time, skipping whitespace
3. Based on the starting character it identifies the token:
   - Alphabetic or `_` → keyword or identifier
   - Digit → constant
   - Operator character → operator
   - Punctuation → special character
4. `categorizeToken()` classifies each token into its final type
5. `main.c` loops calling `getNextToken()` until EOF and prints each token with its type

---

## Limitations

- Only integer constants are supported (no float, hex, or string literals)
- Multi character operators like `==`, `!=`, `<=`, `>=` are not supported
- Comments (`//` and `/* */`) are not handled and may produce unknown tokens
- Preprocessor directives (`#include`, `#define`) are not tokenized

---

## Author

Sneha
