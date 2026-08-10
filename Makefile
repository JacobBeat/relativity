main: main.o 
	g++ -lglfw main.o -o main 

main.o: main.cpp  
	g++ -c main.cpp  
