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
CharType type(const char c);
#ifdef DEBUG
void debug(const char* format, ...);
void showCalc(const Calc* calc);
#endif
void error(const char* format, ...);
int precedence(const char sign);
bool doCalculation(Calc* calc, const char sign);
bool proccessInput(Calc* calc, const char* string);

#endif

