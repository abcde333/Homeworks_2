CC = g++
CXXFLAGS = -c
TARGET = do-command
OBJECTS = do_command.o
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

do_command.o: do_command.cpp
	$(CC) $(CXXFLAGS)  do_command.cpp

clean:
	rm -f $(TARGET) $(OBJECTS)
