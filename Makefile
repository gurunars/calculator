clean:
	rm calc.exe
	rm test.exe

build:
	gcc -o calc src/*.c -lm

test:
	gcc -lm test.c src/stack.c src/calc.c -o test.exe

debug:
	gcc -o calc src/*.c -lm -DDEBUG
