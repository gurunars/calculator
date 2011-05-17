Algorithm
---------

1. Open the input and the output.

2. Do:
    2.1. Get next token from input.
    2.2. Choose:
        - if token is an operand, then write it to output.
        - else if token is an operator, then:
            + while ( (token's precedence) ≤ (precedence of the operator on top of the operator-stack) ):
                * pop the top operator from the operator-stack and write it to output.
            + push the token onto the operator-stack.
        - else if token is '(', then push it onto the operator-stack (with precedence -1).
        - else if token is ')', then:
            + while (the top of the operator-stack is not a '(' ):
                * pop the top operator from the operator-stack and write it to output.
                * if the operator-stack becomes empty, then a parentheses-balancing error has occurred. Complain bitterly.
            + pop the '(' off the operator-stack; discard it and the token.
        - else some token error has occurred. Abandon the conversion.
    2.3. Repeat these steps as long as input tokens are available.

3. While (the operator-stack is not empty):
    - pop the top operator from the operator-stack and write it to output.
    - If (the top of the operator-stack is a '(' ), then a parentheses-balancing error has occurred. Complain bitterly.

4. Close the input and the output.

Operator Precedence Levels
--------------------------
==========  ========    ==================================
precedence  operator    (typical operation)
==========  ========    ==================================
9           ^           exponentiation
8           \*          multiplication
8           /           division
8           %           remainder
6           \+          addition
6           \-          subtraction
-1          (           begin-grouping
?           )           end-grouping (no precedence)
==========  ========    ==================================

Usage
-----

1. Keep digits in a file and perform calculations
   ``calc.exe -f FILE_NAME``
2. Pass digits as input in terminal
   ``calc.exe -i "PATTERN"``

Compilation instructions
------------------------

Use ``make build`` to compile the sources.
Use ``make debug`` to compile the sources in a debug mode.
Use ``make test`` and ``./test.exe`` to run unittests.
Use ``valgrind --tool=memcheck calc.exe ...`` to check memory leaks.
