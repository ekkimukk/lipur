exec = lipur.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -std=c99 -Wall -ledit -lm

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

clean:
	rm $(exec) $(objects)
