# Regular Expression Parser in C++

This is a C++ implementation of a regular expression parser that can parse and interpret basic regular expressions.

## Features

- Parses basic regular expressions containing:
  - Characters
  - Alternation (`|`)
  - Grouping `()`
  - Repetition `*`
- Supports displaying the parsed regular expression
- Includes a parser class `RegExParser` that handles the parsing logic
- Implements various classes representing different components of regular expressions:
  - `RegEx`: Base class for all types of regular expressions
  - `Primitive`: Represents individual characters
  - `Choice`: Represents an alternation between regular expressions
  - `Sequence`: Represents a sequence of regular expressions
  - `Repetition`: Represents a repetition of a regular expression

## Usage

### Prerequisites

- C++ compiler supporting C++11

### Building the Parser

1. Clone the repository:
   ```bash
   git clone https://github.com/abdokin/re-parser.git
   ```

2. Build the parser:
   ```bash
   make 
   ```

### Running the Parser

To parse a regular expression, run the built executable with the regular expression as an argument:
```bash
./re "your-regular-expression"
```

Replace `"your-regular-expression"` with the regular expression you want to parse.

## Example

### Parsing a Regular Expression

Suppose you have the regular expression `a(b|c)*`:

```bash
./re "a(b|c)*"
```

The parser will display the parsed regular expression.

## Contribution

Feel free to contribute to this project by forking it and sending pull requests.

---

Modify and extend this template as needed to include specific installation instructions, usage examples, contributing guidelines, license information, etc., based on your project's requirements and structure.