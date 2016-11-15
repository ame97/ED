prueba: prueba.o
	g++ -o prueba prueba.o
	
principal: principal.o
	g++ -o principal principal.o
	
	

prueba.o: prueba.cpp
	g++ -I./ -std=c++0x -c prueba.cpp -o prueba.o -g -Wall
	
principal.o: principal.cpp
	g++ -I./ -std=c++0x -c principal.cpp -o principal.o


	
mrproper:
	rm ./prueba ./principal ./*.o
