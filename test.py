import commands


CASES = (
    ("1+1", "2.000000"),
    ("(1+1)*2", "4.000000"),
    ("1+(1", "Error: open bracket(s) was not closed"),
    (".1+2", "Error: dot not surrounded with digits @ 0"),
    ("1.+3", "Error: digit ends with a dot @ 2"),
    ("1+4)", "Error: close bracket did not match open bracket."),
    ("1++4", "Error: sign + in illegal place @ 2"),
    ("2+1-", "Error: not enough digits to perform calculation"),
    ("(((21*14-16)/5+5-18)*2-100)+820-1", "804.200000"),
    ("2^2^2-15-14-12-11-10^5", "-100036.000000"),
    ("1+200000000000000000000000000000000000000000000000000000000000000000000",
     "Error: max digit size of 20 symbols exceeded @ 22")
)


def test_calc(expr, result):
    test_calc.counter += 1
    print "CASE %d" % test_calc.counter
    expr = "./calc -i \"%s\"" % expr
    output = commands.getstatusoutput(expr)[1]
    if output.replace("\n", "") == result:
        print "OK"
    else:
        test_calc.failures += 1
        print "FAIL"
        print "Expr: %s" % expr
        print "Expected: \"%s\"" % result
        print "Actual: \"%s\"" % output
test_calc.counter = 0
test_calc.failures = 0


def run_tests():
    commands.getstatusoutput("make build")
    for case in CASES:
        test_calc(case[0], case[1])
    print "Cases run: %d" % test_calc.counter
    if test_calc.failures:
        print "Failed cases: %d" % test_calc.failures
    else:
        print "All tests passed."


run_tests()
