CC = gcc
CFLAG = -Wall -Wextra -lprint_board -L ./util
EXE = scrabble
OBJ = scrabble.o

build: $(EXE)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAG)

$(EXE): $(OBJ)
	$(CC) $^ $(CFLAG) -o $(EXE)

run:
	./$(EXE)

.PHONY: clean

clean:
	rm -f *.o $(EXE)

