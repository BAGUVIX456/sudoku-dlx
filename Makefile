CC := g++

SRC := src
EXE := bin/sudoku
COMPILE := bin

all: $(EXE)

$(EXE):
	if [ ! -d "$(COMPILE)" ]; then mkdir $(COMPILE); fi && $(CC) $(SRC)/sudoku.cpp -o $@

clean:
	rm -rf $(EXE)
