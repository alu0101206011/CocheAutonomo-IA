CC = g++
CFLAGS = -g -Wall -std=c++17
OBJ = ./obj/board.o ./obj/board_maker.o ./obj/car.o ./obj/main.o
EXEC = Board_Test

all: $(OBJ) 
	$(CC) $(CFLAGS) -o ./bin/$(EXEC) $^

run: clean all
	./$(BIN)/$(EXEC)

./obj/%.o: ./src/%.cpp 
	$(CC) -c -o $@ $<


.PHONY: clean

clean:
	rm ./bin/*
	rm ./obj/*