CC = mpic++
CFLAGS = -O3 -lm

all : compile clean

compile: main others algo
	$(CC) $(CFLAGS) main.o others.o algo.o -o task23

main: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

others: others.cpp
	$(CC) $(CFLAGS) -c others.cpp

algo: algo.cpp
	$(CC) $(CFLAGS) -c algo.cpp

clean:
	rm -rf *o compile