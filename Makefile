main: main.o
	g++ -L./imebraLib/ -Wl,-rpath,./imebraLib/ -Wall -o main main.o -limebra -lncurses
main.o: main.cpp
	g++ -I./include/ -o main.o -c main.cpp