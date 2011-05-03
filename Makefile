clear:
	rm calc.exe

build:
	gcc -lm *.c -o calc.exe

debug:
	sed -i 's/\/\/#define DEBUG/#define DEBUG/g' ./*.c
	make build
	sed -i 's/#define DEBUG/\/\/#define DEBUG/g' ./*.c
