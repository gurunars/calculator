clean:
	rm calc.exe

build:
	gcc -lm src/*.c -o calc.exe

debug:
	sed -i 's/\/\/#define DEBUG/#define DEBUG/g' ./src/*.c
	make build
	sed -i 's/#define DEBUG/\/\/#define DEBUG/g' ./src/*.c
