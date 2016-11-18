principal: principal.o
	g++ -o principal.exe principal.o

prueba: prueba.o
	g++ -o prueba.exe prueba.o
	

prueba.o: prueba.cpp
	g++ -I./ -std=c++0x -c prueba.cpp -o prueba.o
	
principal.o: principal.cpp
	g++ -I./ -std=c++0x -c principal.cpp -o principal.o

	
	
mrproper:
	rm ./*.exe ./*.o