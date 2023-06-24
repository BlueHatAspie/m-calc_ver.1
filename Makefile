CC = gcc
FLAGS = -Wall

.PHONY: clean

app: mcalc.o
	$(CC) -o app mcalc.o $(FLAGS)
	rm *.o
	./app

mcalc.o:
	$(CC) -c src/mcalc.c

clean:
	rm app
