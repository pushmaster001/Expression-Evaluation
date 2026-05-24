# Expression Evaluator

A robust C++ console application that parses, validates, and evaluates mathematical expressions. 

This program takes a standard mathematical expression (Infix notation), validates its syntax, converts it to Postfix notation, and calculates the final result. It also features dynamic variable recognition, allowing users to input algebraic expressions and assign values to variables at runtime.

## 🚀 Features

* **Syntax Validation:** Automatically checks for balanced parentheses `()`, brackets `[]`, and braces `{}`.
* **Infix to Postfix Conversion:** Utilizes stack data structures to reliably convert expressions based on standard operator precedence.
* **Variable Support:** Detects variables within the expression and prompts the user to enter their specific integer values before calculation.
* **Basic Arithmetic:** Supports addition (`+`), subtraction (`-`), multiplication (`*`), and division (`/`).
* **Error Handling:** Includes safeguards for logical errors, syntax errors, and runtime errors (like division by zero).

## 🛠️ Technologies Used

* **Language:** C++ (Standard Template Library)
* **Core Data Structures:** `std::stack`, `std::vector`, `std::map`, `std::set`

## 💻 How to Run

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/pushmaster001/Expression-Evaluation.git](https://github.com/pushmaster001/Expression-Evaluation.git)
   cd Expression-Evaluation
