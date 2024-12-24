CC = g++                    
CFLAGS = -std=c++11 -Wall    
OUT = interactive-shell      
SRC = interactive_shell.cpp  
OBJ = interactive_shell.o    

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -rf $(OBJ) $(OUT)
