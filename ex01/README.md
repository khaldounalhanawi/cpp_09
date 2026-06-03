# ex01 — Reverse Polish Notation (RPN)

## Overview

This program evaluates a mathematical expression written in **Reverse Polish Notation (RPN)**, also known as postfix notation. In RPN, operators follow their operands, eliminating the need for parentheses.

The program takes the expression as a single command-line argument and prints the result to standard output. Any error is reported to standard error.

## Usage

```
./RPN "<expression>"
```

Supported operators: `+ - * /`  
Input operands must be single digits (0–9). The result is not bounded.

## Examples

```
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"   → 42
./RPN "7 7 * 7 -"                     → 42
./RPN "1 2 * 2 / 2 * 2 4 - +"        → 0
```

## How It Works

Tokens are read left to right:
- **Operand** → pushed onto a stack
- **Operator** → pops two operands, computes the result, pushes it back

At the end, the stack must contain exactly one value — the result.

A `std::stack<int, std::list<int>>` is used as the underlying container.

---

## Edge Cases Handled

### Invalid or empty input
```
./RPN ""         → Error   (empty argument)
./RPN "   "      → Error   (whitespace-only)
```

### Brackets or multi-char tokens
```
./RPN "(1 + 1)"  → Error   ('(' is not a digit or operator)
./RPN "12 3 +"   → Error   ("12" is more than one character)
```

### Too few operands for an operator
```
./RPN "1 +"      → Error   (only one value on stack when '+' is encountered)
./RPN "+"        → Error   (stack is empty)
```

### Too many operands (incomplete expression)
```
./RPN "1 2 3 +"  → Error   (stack has 2 values at the end instead of 1)
```

### Division by zero
```
./RPN "5 0 /"    → Error
```

### Negative intermediate results
The stack may hold negative values mid-expression; this is handled correctly:
```
./RPN "1 9 - 9 - 9 -"   → -26
```
Trace: `1 - 9 = -8` → `-8 - 9 = -17` → `-17 - 9 = -26`

### Integer overflow
Operations are promoted to `long long` before execution and checked against `INT_MAX` / `INT_MIN`. If the result would overflow a 32-bit integer, an error is reported:
```
./RPN "9 9 9 9 9 9 9 9 9 9 * * * * * * * * *"   → Error   (9^10 > INT_MAX)
```

Negative overflow is also caught:
```
./RPN "0 9 9 9 9 9 9 9 9 9 * * * * * * * * - 9 *"   → Error   (-9^9 * 9 < INT_MIN)
```
