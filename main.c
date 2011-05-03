#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

//#define DEBUG


int main(int argc, char *argv[]){

    FILE* fp;
    int chars_in_file;
    char* content;
    double* temp_double;
    Calc* calc;

    if (argc < 2) {
        printf("No file specified.\n");
        exit(1);
    }

    if((fp = fopen(argv[1], "r"))==NULL) {
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

    calc = createCalc();
    if (proccessInput(calc, content)) {
        temp_double = pop(calc->output);
        printf("Result: %f\n", *temp_double);
        free(temp_double);
    }
    free(content);
    deleteCalc(calc);

}
