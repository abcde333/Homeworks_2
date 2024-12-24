CC=g++
CFLAGS=-std=c++11 -Wall
LDFLAGS=-pthread

all: prime-calculator

prime-calculator: prime_calculator.o
	$(CC) $(CFLAGS) prime_calculator.o -o prime-calculator $(LDFLAGS)

prime_calculator.o: prime_calculator.cpp
	$(CC) $(CFLAGS) -c prime_calculator.cpp

clean:
	rm -f *.o prime-calculator

