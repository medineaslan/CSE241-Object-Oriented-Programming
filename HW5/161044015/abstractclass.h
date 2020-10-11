#ifndef ABSTRACTCLASS_H
#define ABSTRACTCLASS_H

#include <string>

using std :: string;

namespace NPuzzleGame
{
	class AbstractBoard
	{
	public:
		virtual void print() = 0;
		virtual void readFromFile(const string fileName) = 0; //Reading from file.
		virtual void writeToFile(const string fileName) = 0; //Writing to file.
		virtual void reset() = 0; //Reset the board.
		virtual bool setSize(int rowValue, int columnValue) = 0; //Set the board size given values.
		virtual bool move(const char move, int controller) = 0; //Makes a move.
		virtual bool isSolved() = 0;
		virtual int operator () (int index_i, int index_j) = 0;
		virtual bool operator == (const AbstractBoard& other)=0;
		bool getFileBoardControl();
        int calculate_digit_number(int number);
		void setFileBoardControl(bool file_board_control_value); //Setting false when reading from file.
		static int NumberOfBoards(); 
		static char lastMove(char myMove);
		static int numberOfMoves(bool solveControl);
		char getLastMove(){return myLastMove;}
		int getNumOfMove(){return myNumberOfMoves;}
		virtual AbstractBoard* clone() const =0;
	private:
      	bool file_board_control = true;
		static char myLastMove ; 
		static int myNumberOfMoves ; 
		static int numberOfBoards ;
	};
}
#endif