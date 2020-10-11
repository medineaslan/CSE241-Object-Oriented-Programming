all: exe

exe:
	g++ -std=c++0x -c abstractclass.cpp
	g++ -std=c++0x -c boardvector.cpp
	g++ -std=c++0x -c boardarray2d.cpp
	g++ -std=c++0x -c boardarray1d.cpp
	g++ -std=c++0x -c 161044015.cpp

	g++ -o exe abstractclass.o boardvector.o boardarray2d.o boardarray1d.o 161044015.o
clean:
	rm *.o exe
