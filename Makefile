main: main.o 
	g++ -lglfw -lGL main.o -o main 

main.o: main.cpp  
	g++ -c main.cpp  
