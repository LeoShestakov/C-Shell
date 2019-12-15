all: main.o
	gcc -o scoop main.c

main.o: main.c
	gcc -c main.c

run:
	./scoop

clean:
	rm *.o

debug: main.c
	gcc -g main.c

gdb: a.out
	gdb a.out