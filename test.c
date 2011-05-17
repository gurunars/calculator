#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./src/calc.h"

#define fail 0
#define pass 1


int assert_ok(char* str, double expected_result) {
    double *temp_double;
    Calc *calc = createCalc();
        if (proccessInput(calc, str)) {
            temp_double = pop(calc->output);
            if (expected_result == *temp_double) {
                printf("OK: %s = %f\n", str, *temp_double);
                return pass;
            }
            printf("NOK: %s = %f != %f\n", str, *temp_double, expected_result);
            free(temp_double);
        }
    deleteCalc(calc);
    return fail;
}


int assert_nok(char* str) {
    double *temp_double;
    Calc *calc = createCalc();
    if (proccessInput(calc, str)) {
        printf("NOK: (calculated?!) %s\n", str);
        return fail;
    }
    deleteCalc(calc);
    printf("OK: (error found) %s\n", str);
    return pass;
}


void main() {
    int passed, failed, n;
    passed = failed = n = 0;
    // Actual tests
    printf("Case %d\n", ++n); if (assert_ok("1+1", 2)) {passed +=1;} else {failed +=1;}
    printf("Case %d\n", ++n); if (assert_nok("1+4)")) {passed +=1;} else {failed +=1;}
    printf("Case %d\n", ++n); if (assert_ok("(1+1+2*2)/3", 2)) {passed +=1;} else {failed +=1;}
    printf("Case %d\n", ++n); if (assert_ok("(1/2+1/2)*6 - (1-(1-2))", 4)) {passed +=1;} else {failed +=1;}
    printf("Case %d\n", ++n); if (assert_nok("1+4+")) {passed +=1;} else {failed +=1;}
    printf("Case %d\n", ++n); if (assert_nok(".1+4")) {passed +=1;} else {failed +=1;}
    printf("Case %d\n", ++n); if (assert_nok("*1+4")) {passed +=1;} else {failed +=1;}
    printf("Case %d\n", ++n); if (assert_nok("1+4.")) {passed +=1;} else {failed +=1;}
    printf("Case %d\n", ++n); if (assert_nok("1+4+(1")) {passed +=1;} else {failed +=1;}
    // Summary
    printf("------------------\n");
    printf("Passed: %d\nFailed: %d\n", passed, failed);
}
