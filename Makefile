clean:
	rm calc.exe
	rm test.exe

build:
	gcc -lm src/*.c -o calc.exe

test:
	gcc -lm test.c src/stack.c src/calc.c -o test.exe

debug:
	sed -i 's/\/\/#define DEBUG/#define DEBUG/g' ./src/*.c
	make build
	sed -i 's/#define DEBUG/\/\/#define DEBUG/g' ./src/*.c
