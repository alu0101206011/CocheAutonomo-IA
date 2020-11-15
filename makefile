CC = g++
CFLAGS = -g -Wall --std=c++17
OBJ = ./obj/board.o ./obj/board_maker.o ./obj/gps.o ./obj/main.o
EXEC = Board_Test

all: $(OBJ)
	$(CC) $(CFLAGS) -o ./bin/$(EXEC) $^

./obj/%.o: ./src/%.cpp 
	$(CC) -c -o $@ $<

run: clean all
	./bin/$(EXEC)

.PHONY: clean

clean:
	rm -f ./bin/*
	rm -f ./obj/*