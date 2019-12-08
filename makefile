all: main.o
	gcc -o scoop main.c

main.o: main.c
	gcc -c main.c

run:
	./scoop

clean:
	rm *.o
