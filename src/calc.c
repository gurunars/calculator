#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "calc.h"

//#define DEBUG


Calc* createCalc() {
    Calc* tempo = malloc(sizeof(Calc));
    tempo->output = createStack();
    tempo->stack = createStack();
    return tempo;
}


void deleteCalc(Calc* calc) {
    deleteStack(calc->output);
    deleteStack(calc->stack);
    free(calc);
}


CharType type(char c) {
    if (isdigit(c)) {
        return DIGIT;
    } else if (c == '.') {
        return DOT;
    } else if (c == '(') {
        return OPEN_BRACKET;
    } else if (c == ')') {
        return CLOSE_BRACKET;
    } else if (c == '+' || c == '-' || c == '*' || c == '/'
             ||c == '%' || c == '^'){
        return SIGN;
    } else if (c == ' ' || c == '\n' || c == '\t') {
        return IGNORE;
    } else {
        return UNEXPECTED_CHAR;
    }
}


#ifdef DEBUG
void debug(char* format, ...) {
    va_list argp;
    va_start(argp, format);
    printf("Debug: ");
    vprintf(format, argp);
    printf("\n");
}


void showCalc(Calc* calc) {

    Node* node;

    printf("----------\n");
    printf("Stack: \n");
    if(hasItems(calc->stack)) {
        node = calc->stack->bottom;
        do {
            printf("%c\n", *(char*) node->data);
        } while(node=node->next);
    }
    printf("Output: \n");
    if(hasItems(calc->output)) {
        node = calc->output->bottom;
        do {
            printf("%f\n", *(double*) node->data);
        } while(node=node->next);
    }
    printf("----------\n");
}
#endif


void error(char* format, ...) {
    va_list argp;
    va_start(argp, format);
    printf("Error: ");
    vprintf(format, argp);
    printf("\n");
}


int precedence(char sign) {
    switch(sign) {
        case '(':
            return -1;
        case '+':
            return 6;
        case '-':
            return 6;
        case '*':
            return 8;
        case '/':
            return 8;
        case '%':
            return 8;
        case '^':
            return 9;
    }
}


bool doCalculation(Calc* calc, char sign) {

    double* temp_double = (double*) pop(calc->output);
    double* temp_double2 = (double*) pop(calc->output);

    if(temp_double && temp_double2) {
        switch(sign) {
            case '+':
                *temp_double = *temp_double2 + *temp_double;
                break;
            case '-':
                *temp_double = *temp_double2 - *temp_double;
                break;
            case '*':
                *temp_double = *temp_double2 * *temp_double;
                break;
            case '/':
                *temp_double = *temp_double2 / *temp_double;
                break;
            case '^':
                *temp_double = pow(*temp_double2, *temp_double);
                break;
            case '%':
                *temp_double = fmod(*temp_double2, *temp_double);
                break;
        }
        push(calc->output, temp_double);
        free(temp_double2);
    } else {
        if(temp_double) {
            free(temp_double);
        }
        error("not enough digits to perform calculation");
#ifdef DEBUG
        showCalc(calc);
#endif
        return false;
    }
}


bool proccessInput(Calc* calc, char* string) {

    int i, j;
    char c, prev_c;
    char* buff;
    double* temp_double;
    bool dot_used, state;
    CharType t;
    CharType prev_t = NONE;

    for(i=0; (c=string[i])!=EOF; i++) {
        if (c == '\0') {
            break;
        }
        switch(type(c)) {

            case DIGIT:
#ifdef DEBUG
                debug("%d digit: %c", i, c);
#endif
                if (prev_t != NONE && prev_t != OPEN_BRACKET &&
                  prev_t != SIGN) {
                    error("digit %c in illegal place @ %d", c, i);
                    return false;
                }
                buff = malloc(sizeof(char)*20); // #1
                dot_used = false;
                buff[0] = c;
                j = 1;
                while (1) {
                    c = string[i+j];
                    t = type(c);
                    if (t == DIGIT || t == DOT) {
                        if (t == DOT && dot_used) {
                            error("another dot in a digit @ %d\n", i+j);
                            return false;
                        } else if (t == DOT && !dot_used) {
#ifdef DEBUG
                            debug("%d dot: %c", i+j, c);
#endif
                            dot_used = true;
                        } else {
#ifdef DEBUG
                            debug("%d digit: %c", i+j, c);
#endif
                        }
                        buff[j] = c;
                        j++;
                    } else {
                        if (type(buff[j-1]) == DOT) {
                            error("digit ends with a dot @ %d", i+j);
                            return false;
                        }
                        buff[j] = '\0';
                        // convert buffer to a digit and push it to output
#ifdef DEBUG
                        debug("double: [%f]", atof(buff));
#endif
                        temp_double = malloc(sizeof(double));
                        *temp_double = atof(buff);
                        push(calc->output, temp_double);
#ifdef DEBUG
                        showCalc(calc);
#endif
                        i += j-1;
                        break;
                    }
                }
                free(buff); //#1
                prev_t = DIGIT;
                break;

            case SIGN:
#ifdef DEBUG
                debug("%d sign: %c", i, c);
#endif
                if (prev_t != NONE && prev_t != CLOSE_BRACKET &&
                  prev_t != DIGIT) {
                    error("sign %c in illegal place @ %d", c, i);
                    return false;
                }
                while (calc->stack->length > 0) {
                    buff = (char*) calc->stack->top->data;
                    if (precedence(c) <= precedence(*buff)) {
                        state = doCalculation(calc, *buff);
                        pop(calc->stack);
                        free(buff);
                        if (!state) {
                            return false;
                        }
                    } else {
                        break;
                    }
                }
                buff = malloc(sizeof(char));
                *buff = c;
                push(calc->stack, buff);
#ifdef DEBUG
                showCalc(calc);
#endif
                prev_t = SIGN;
                break;

            case IGNORE:
#ifdef DEBUG
                debug("%d ignore: %c", i, c);
#endif
                break;

            case OPEN_BRACKET:
#ifdef DEBUG
                debug("%d open bracket: %c", i, c);
#endif
                if (prev_t != NONE && prev_t != OPEN_BRACKET && prev_t != SIGN) {
                    error("open bracket in illegal place @ %d", i);
                    return false;
                }
                buff = malloc(sizeof(char));
                *buff = c;
                push(calc->stack, buff);
                prev_t = OPEN_BRACKET;
                break;

            case CLOSE_BRACKET:
#ifdef DEBUG
                debug("%d close bracket: %c", i, c);
#endif
                if (prev_t != CLOSE_BRACKET && prev_t != DIGIT) {
                    error("close bracket in illegal place @ %d", i);
                    return false;
                }
                while(1) {
                    buff = pop(calc->stack);

                    if(!buff) {
                        error("close bracket did not match open bracket.");
                        return false;
                    }

#ifdef DEBUG
                    debug("poped a sign: %c", *buff);
                    showCalc(calc);
#endif

                    if(type(*buff) == OPEN_BRACKET) {
                        free(buff);
                        break;
                    } else {
                        doCalculation(calc, *buff);
                        free(buff);
                    }
                }
                prev_t = CLOSE_BRACKET;
                break;

            case DOT:
                error("dot not surrounded with digits @ %d", i);
                return false;

            case UNEXPECTED_CHAR:
                error("unexpected character %c @ %d", c, i);
                return false;
        }
    }

    if (hasItems(calc->stack)) {
        while(hasItems(calc->stack)) {
            buff = (char*) pop(calc->stack);
            if(type(*buff) == OPEN_BRACKET) {
                error("open bracket(s) was not closed");
                return false;
            }
            state = doCalculation(calc, *buff);
            free(buff);
            if (!state) {
                return false;
            }
        }
    }

    if (calc->output->length == 0) {
        error("RPN calculator output has no values.\n");
        return false;
    } else if (calc->output->length == 1) {
        return true;
    } else {
        error("RPN calculator output has more then one value.");
        while(hasItems(calc->output)) {
            temp_double = (double*) pop(calc->output);
            printf("%f\n", *temp_double);
            free(temp_double);
        }
        return false;
    }

}
