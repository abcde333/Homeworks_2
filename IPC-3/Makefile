CXX = g++
CXXFLAGS = -std=c++11 -Wall -pthread

all: first second

first: first.cpp shared_array.h
	$(CXX) $(CXXFLAGS) -o first first.cpp

second: second.cpp shared_array.h
	$(CXX) $(CXXFLAGS) -o second second.cpp

clean:
	rm -f first second
