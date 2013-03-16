build:
	gcc -o calc src/*.c -lm

clean:
	rm calc

debug:
	gcc -o calc src/*.c -lm -DDEBUG
