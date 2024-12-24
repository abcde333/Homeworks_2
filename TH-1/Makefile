CC = g++
CFLAGS = -std=c++11 -Wall -pthread
OUT = array-summary
SRC = array_summary.cpp
OBJ = array_summary.o

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -rf $(OBJ) $(OUT)

.PHONY: all clean
