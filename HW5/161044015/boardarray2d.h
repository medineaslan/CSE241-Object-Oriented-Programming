#ifndef BOARDARRAY2D_H
#define BOARDARRAY2D_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "abstractclass.h"

using namespace std;

namespace NPuzzleGame
{
	class BoardArray2D : public AbstractBoard
	{
	public:
		BoardArray2D();
		BoardArray2D(const BoardArray2D& other);
		int getRow()const;
		int getColumn()const;
		virtual void print();
		virtual void readFromFile(const string fileName); //Reading from file.
		virtual void writeToFile(const string fileName); //Writing to file.
		virtual void reset(); //Reset the board.
		virtual bool setSize(int rowValue, int columnValue); //Set the board size given values.
		void initialize2DBoard();
		virtual bool move(const char move, int controller); //Makes a move.
		virtual bool isSolved();
		virtual int operator () (int index_i, int index_j);
		virtual bool operator == (const AbstractBoard& other);
		BoardArray2D& operator = (const BoardArray2D& other);
		inline AbstractBoard* clone() const {return new BoardArray2D(*this);}
		~BoardArray2D( );
	private:
		int** board2D;
		int row;
		int column;
	};
}

#endif 
