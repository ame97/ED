CPP = g++ -std=c++0x
INC = .
BIN = .
SRC = .
OBJ = .
DOC = .

all: $(BIN)/principal $(BIN)/prueba

# ----------------------------------------------- #

$(BIN)/principal: $(OBJ)/principal.o
	$(CPP) $(OBJ)/principal.o -o $(BIN)/principal.exe

$(BIN)/prueba: $(OBJ)/prueba.o
	$(CPP) $(OBJ)/prueba.o -o $(BIN)/prueba.exe

# ----------------------------------------------- #

$(OBJ)/prueba.o: $(SRC)/prueba.cpp
	$(CPP) -I$(INC) -c $(SRC)/prueba.cpp -o $(OBJ)/prueba.o
	
$(OBJ)/principal.o: $(SRC)/principal.cpp
	$(CPP) -I$(INC) -c $(SRC)/principal.cpp -o $(OBJ)/principal.o

# ----------------------------------------------- #

doxy:
	doxygen $(DOC)/docPractica.txt
	mv html $(DOC)/HTML
	mv latex $(DOC)/LaTeX

# ----------------------------------------------- #

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*.exe
	rm $(DOC)/HTML
	rm $(DOC)/LaTeX
