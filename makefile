SRC = ./SRC
OBJ = ./OBJ
INC = ./INC
BIN = ./BIN
DOC = ./DOC

all: $(BIN)/Principal

$(BIN)/Principal: $(OBJ)/principal.o
	g++ -o $(BIN)/Principal $(OBJ)/principal.o

$(OBJ)/principal.o: $(SRC)/principal.cpp
	g++ -I$(INC) -std=c++11 -c $(SRC)/principal.cpp -o $(OBJ)/principal.o

mrproper:
	rm -f $(BIN)/* $(OBJ)/*.o   
	rm -Rf $(DOC)/HTML $(DOC)/LaTeX
doxy:
	doxygen $(DOC)/doxPractica.txt
	mv html $(DOC)/HTML
	mv latex $(DOC)/LaTeX
