#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H

#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "abstractclass.h"

using namespace std;

namespace NPuzzleGame
{
	class BoardVector : public AbstractBoard
	{
	public:
		BoardVector(int rowValue, int columnValue);
		virtual void print();
		virtual void readFromFile(const string fileName); //Reading from file.
		virtual void writeToFile(const string fileName); //Writing to file.
		virtual void reset(); //Reset the board.
		virtual bool setSize(int rowValue, int columnValue); //Set the board size given values.
		void initializeBoard(int rowValue, int columnValue);
		virtual bool move(const char move, int controller); //Makes a move.
		virtual bool isSolved();
		virtual int operator () (int index_i, int index_j);
		virtual bool operator == (const AbstractBoard& other);
		inline AbstractBoard* clone() const {return new BoardVector(*this);}
	private:
		vector<vector<int>> board;
	};
}

#endif 