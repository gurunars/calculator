#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "calc.h"

typedef enum {file, console_input, unknown} InputType;

InputType inputType(char* argument) {
    if (strcmp(argument, "-f") == 0) {
        return file;
    } else if (strcmp(argument, "-i") == 0) {
        return console_input;
    } else {
        return unknown;
    }
}

void showHelp() {
    printf("Use '-f' option to fetch input from file or '-i' to fetch it from"
           " console directly.\n");
}

int main(int argc, char *argv[]){

    FILE* fp;
    int n_chars;
    char* content;
    double* temp_double;
    Calc* calc;
    
    if (argc < 3) {
        printf("No args specified.\n");
        showHelp();
        exit(1);
    }

    InputType input_t = inputType(argv[1]);
    
    switch(input_t) {
        case file:
            if((fp = fopen(argv[2], "r"))==NULL) {
                printf("Cannot open file.\n");
                exit(1);
            }
            fseek(fp, 0, SEEK_END);
            n_chars = ftell(fp);
            fseek(fp, 0, SEEK_SET);
#ifdef DEBUG
            printf("Chars in file: %d\n", n_chars);
#endif
            content = xmalloc(sizeof(char)*(n_chars+1));
            fread(content, n_chars, 1, fp);
            content[n_chars] = EOF;
            fclose(fp);
            break;
        case console_input:
            n_chars = strlen(argv[2]);
            content = xmalloc(sizeof(char)*(n_chars+1));
            strcpy(content, argv[2]);
#ifdef DEBUG
            printf("Input: [%s]\n", content);
            printf("Chars in input: %d\n", n_chars);
#endif
            break;
        case unknown:
            printf("Unknown option.\n");
            showHelp();
            return 1;
    }

    calc = createCalc();
    if (proccessInput(calc, content)) {
        temp_double = pop(calc->output);
        printf("%f\n", *temp_double);
        free(temp_double);
    }
    free(content);
    deleteCalc(calc);

}
