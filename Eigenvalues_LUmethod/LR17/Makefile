CC = g++
CFLAGS = -O3 -fsanitize=address -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused \
	-Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith \
         -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align \
         -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual \
         -Wno-suggest-attribute=format -static-libasan

all : compile clean

compile: main.o array_generator.o array_output.o findValues.o
	$(CC) $(CFLAGS) main.o array_generator.o array_output.o findValues.o -o task17

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

array_generator.o: array_generator.cpp
	$(CC) $(CFLAGS) -c array_generator.cpp

array_output.o: array_output.cpp
	$(CC) $(CFLAGS) -c array_output.cpp

invert_matrix.o: findValues.cpp
	$(CC) $(CFLAGS) -c findValues.cpp

clean:
	rm -rf *o compile