clean:
	rm calc

build:
	gcc -o calc src/*.c -lm

debug:
	gcc -o calc src/*.c -lm -DDEBUG
