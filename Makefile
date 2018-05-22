list: list.o
	g++ -L./imebraLib/ -Wl,-rpath,./imebraLib/ -Wall -o list list.o -limebra
list.o: list.cpp
	g++ -I./include/ -o list.o -c list.cpp