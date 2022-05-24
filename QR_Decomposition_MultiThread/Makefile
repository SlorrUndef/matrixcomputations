CC = g++
CFLAGS = -O3 -fsanitize=address -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused \
	-Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith \
         -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align \
         -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual \
         -Wno-suggest-attribute=format -static-libasan -lpthread -lm

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