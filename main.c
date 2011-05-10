#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

//#define DEBUG

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
    int chars_in_file;
    char* content;
    double* temp_double;
    Calc* calc;

    if (argc < 3) {
        printf("No args specified.\n");
        showHelp();
        exit(1);
    }

    switch(inputType(argv[1])) {
        case file:
            if((fp = fopen(argv[2], "r"))==NULL) {
                printf("Cannot open file.\n");
                exit(1);
            }
            fseek(fp, 0, SEEK_END);
            chars_in_file = ftell(fp);
            fseek(fp, 0, SEEK_SET);
#ifdef DEBUG
            printf("Chars in file: %d\n", chars_in_file);
#endif
            content = malloc(sizeof(char)*(chars_in_file+1));
            fread(content, chars_in_file, 1, fp);
            content[chars_in_file] = EOF;
            fclose(fp);
            break;
        case console_input:
            content = argv[2];
            break;
        case unknown:
            printf("Unknown option.\n");
            showHelp();
            return 1;
    }

    calc = createCalc();
    if (proccessInput(calc, content)) {
        temp_double = pop(calc->output);
        printf("Result: %f\n", *temp_double);
        free(temp_double);
    }
    free(content);
    deleteCalc(calc);

}
