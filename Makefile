main: main.o shader.o 
	g++ -lGLEW -lglfw -lGL main.o shader.o -o main 

main.o: main.cpp  
	g++ -c main.cpp  
shader.o: shader.cpp
	g++ -c shader.cpp
