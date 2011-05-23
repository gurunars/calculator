clean:
	rm calc
	rm test

build:
	gcc -o calc src/*.c -lm

test:
	gcc -o test test.c src/stack.c src/calc.c -lm

debug:
	gcc -o calc src/*.c -lm -DDEBUG
