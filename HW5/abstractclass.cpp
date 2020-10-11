#include <string>
#include <cstdlib>
#include <iostream>
#include "abstractclass.h"

using std :: cout;
using std :: endl;
using std :: ios;

namespace NPuzzleGame
{
	int AbstractBoard :: NumberOfBoards ()
	{
		return numberOfBoards;
	}
	char AbstractBoard :: lastMove (char myMove)
	{
		myLastMove = myMove;

		return myLastMove;
	}
	int AbstractBoard :: numberOfMoves(bool solveControl)
	{
		if(solveControl){
			myNumberOfMoves++;
		}
		return myNumberOfMoves;
	}
	bool AbstractBoard :: getFileBoardControl()
	{
		return file_board_control;
	}
	int AbstractBoard :: calculate_digit_number(int number)
	{
		int count = 0;

		while(number > 0){
			number = number / 10;
			count++;
		}
		return count;
	}

	
	void AbstractBoard :: setFileBoardControl(bool file_board_control_value)
	{
		file_board_control = file_board_control_value;
	}
}
