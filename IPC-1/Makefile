CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = signal-echo

all: $(TARGET)

$(TARGET): signal-echo.cpp
	$(CC) $(CFLAGS) -o $(TARGET) signal-echo.cpp

clean:
	rm -f $(TARGET)
