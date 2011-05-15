#ifndef CALC_G
#define CALC_G

#include "stack.h"

typedef enum {
    NONE, DOT, OPEN_BRACKET, CLOSE_BRACKET, SIGN, IGNORE, DIGIT, UNEXPECTED_CHAR
} CharType;


typedef struct calc {
    Stack* output;
    Stack* stack;
} Calc;


Calc* createCalc();
void deleteCalc(Calc* calc);
CharType type(char c);
#ifdef DEBUG
void debug(char* format, ...);
void showCalc(Calc* calc);
#endif
void error(char* format, ...);
int precedence(char sign);
bool doCalculation(Calc* calc, char sign);
bool proccessInput(Calc* calc, char* string);

#endif

