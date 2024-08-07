all:
	gcc -std=c99 -Wall *.c -ledit -o main -lm
	./main
