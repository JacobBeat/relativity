main: main.o shader.o 3vec.o
	g++ -lGLEW -lglfw -lGL main.o shader.o 3vec.o -o main 

main.o: main.cpp  
	g++ -c main.cpp  
shader.o: shader.cpp
	g++ -c shader.cpp
3vec.o: 3vec.cpp
	g++ -c 3vec.cpp
