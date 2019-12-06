all: main.o functions.o
	gcc -o scoop main.c functions.c

main.o: main.c functions.h
	gcc -c main.c

functions.o: functions.c functions.h
	gcc -c functions.c

run:
	./scoop

clean:
	rm *.o
