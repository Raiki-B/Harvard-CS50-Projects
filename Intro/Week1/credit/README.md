# Credit

**CS50 Problem Set 1**

This program determines whether a given credit card number is valid according to Luhn’s Algorithm and identifies the issuing network (e.g., AMEX, MASTERCARD, VISA).

## Problem Description  
> https://cs50.harvard.edu/x/psets/1/credit/

Write a program that prompts the user for a credit card number and then reports whether it is a valid AMEX, MASTERCARD, VISA, or INVALID card number.

### Example Output
```text
Number: 4003600000000014
VISA
```

## Concepts Used
- **Input validation** with `get_long()`
- **Arrays** for digit storage and manipulation
- **String comparison** using `strcmp()`
- **Modular arithmetic** for digit extraction
- **Custom digit manipulation functions**
- **Luhn’s Algorithm** to check card validity
- **Constants and macros** with `#define`
- **Function decomposition** for clean structure and reusability
- **Control flow** with `if/else`, loops (`for`, `do...while`)

## Source File
- [`credit.c`](./credit.c)

## [Status](https://submit.cs50.io/users/Raiki-B/cs50/problems/2025/x/credit)
- ✅ 17/17 tests passed  
- ✅ 100% on style score
