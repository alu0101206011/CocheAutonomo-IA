CC = g++
CFLAGS = -g -Wall -std=c++17
OBJ = ./bin/board.o ./bin/board_maker.o ./bin/car.o ./bin/main.o
EXEC = Board_Test

all: $(OBJ)
	$(CC) $(CFLAGS) -o ./bin/$(EXEC) $^

./bin/%.o: ./src/%.cpp 
	$(CC) -c -o $@ $<

run: clean all
	./bin/$(EXEC)

.PHONY: clean

clean:
	rm -f ./bin/*
	rm -f ./obj/*