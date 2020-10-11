all: exe

exe:
	g++ -std=c++0x -c GTUContainer.cpp
	g++ -std=c++0x -c GTUSet.cpp
	g++ -std=c++0x -c GTUVector.cpp
	g++ -std=c++0x -c GTUIterator.cpp
	g++ -std=c++0x -c GTUIteratorConst.cpp
	g++ -std=c++0x -c 161044015.cpp

	g++ -o exe GTUContainer.o GTUSet.o GTUVector.o GTUIterator.o GTUIteratorConst.o 161044015.o
clean:
	rm *.o exe
