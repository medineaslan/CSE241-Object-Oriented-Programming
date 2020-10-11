#ifndef BOARDARRAY1D_H
#define BOARDARRAY1D_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "abstractclass.h"

using namespace std;

namespace NPuzzleGame
{
	class BoardArray1D : public AbstractBoard
	{
	public:
		BoardArray1D();
		BoardArray1D(const BoardArray1D& other);
		virtual void print();
		virtual void readFromFile(const string fileName); //Reading from file.
		virtual void writeToFile(const string fileName); //Writing to file.
		virtual void reset(); //Reset the board.
		virtual bool setSize(int rowValue, int columnValue); //Set the board size given values.
		void initialize1DBoard();
		virtual bool move(const char move, int controller); //Makes a move.
		virtual bool isSolved();
		virtual int operator () (int index_i, int index_j);
		virtual bool operator == (const AbstractBoard& other);
		BoardArray1D& operator = (const BoardArray1D& other);
		~BoardArray1D( );
		inline AbstractBoard* clone() const {return new BoardArray1D(*this);}
	private:
		int* board1D;
		int size1;
		int size2;
	};
}

#endif 

