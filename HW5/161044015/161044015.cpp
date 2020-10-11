#include <iostream>
#include "abstractclass.h"
#include "boardvector.h"
#include "boardarray2d.h"
#include "boardarray1d.h"

using std :: cout;
using std :: endl;
using std :: ios;

using namespace NPuzzleGame;

char AbstractBoard:: myLastMove = 'S';
int AbstractBoard:: myNumberOfMoves = 0;
int AbstractBoard:: numberOfBoards = 0;

void driverBoardVector()
{
	int vectorSize;

	cout << "BOARDVECTOR CLASS" << endl;
	
	cout << "Please enter the problem size" << endl;

	cin >> vectorSize;

	BoardVector boardVec1(vectorSize,vectorSize);
	boardVec1.setSize(vectorSize,vectorSize);

	BoardVector boardVec2(vectorSize,vectorSize);
	boardVec2.setSize(vectorSize,vectorSize);

	boardVec1.print();

	cout << "Initial value of lastMove " << boardVec1.getLastMove() << endl;


	cout << "Move:R" << endl;
	boardVec1.move('R',1);
	AbstractBoard :: lastMove('R');


	boardVec1.print();

	cout << "Move:L" << endl;
	boardVec1.move('L',1);
	AbstractBoard :: lastMove('L');

	boardVec1.print();

	cout << "Move:U" << endl;
	boardVec1.move('U',1);
	AbstractBoard :: lastMove('U');

	boardVec1.print();

	cout << "Move:D" << endl;
	boardVec1.move('D',1);
	AbstractBoard :: lastMove('D');

	boardVec1.print();

	cout << "Please enter file name for writing file" << endl;
	string fileNameVec;
	cin >> fileNameVec;
	boardVec1.writeToFile(fileNameVec);
	cout << "Please enter file name for reading file" << endl;
	cin >> fileNameVec;
	boardVec1.readFromFile(fileNameVec);

	cout << "Move:R" << endl;
	boardVec1.move('R',1);
	AbstractBoard :: lastMove('R');

	boardVec1.print();

	cout << "Move:L" << endl;
	boardVec1.move('L',1);
	AbstractBoard :: lastMove('L');

	boardVec1.print();

	cout << "Reset" << endl;
	boardVec1.reset();

	cout << "isSolved : "<< boardVec1.isSolved() << endl;

	cout << "Final value of lastMove " << boardVec1.getLastMove() << endl;

}
void driverBoardArray1D()
{
	cout << "BOARDARRAY1D CLASS" << endl;

	int size1D;

	cout << "Please enter the problem size" << endl;
	cin >> size1D;

	BoardArray1D boardArr1D;

	cout << boardArr1D.getNumOfMove() << endl;

	boardArr1D.setSize(size1D,size1D);
	boardArr1D.print();

	cout << "Move:R" << endl;
	bool control = boardArr1D.move('R',1);
	AbstractBoard :: numberOfMoves(control);
	boardArr1D.print();


	cout << "Move:L" << endl;
	control = boardArr1D.move('L',1);
	AbstractBoard :: numberOfMoves(control);

	boardArr1D.print();

	cout << "Move:U" << endl;
	control = boardArr1D.move('U',1);
	AbstractBoard :: numberOfMoves(control);

	boardArr1D.print();

	cout << "Move:D" << endl;
	control = boardArr1D.move('D',1);
	AbstractBoard :: numberOfMoves(control);

	boardArr1D.print();

	cout << "Please enter file name for writing file" << endl;
	string fileName1D;
	cin >> fileName1D;
	boardArr1D.writeToFile(fileName1D);
	cout << "Please enter file name for reading file" << endl;
	cin >> fileName1D;
	boardArr1D.readFromFile(fileName1D);

	cout << "Move:R" << endl;
	control = boardArr1D.move('R',1);
	AbstractBoard :: numberOfMoves(control);

	boardArr1D.print();

	cout << "Move:L" << endl;
	control = boardArr1D.move('L',1);
	AbstractBoard :: numberOfMoves(control);

	boardArr1D.print();

	cout << "Reset" << endl;
	boardArr1D.reset();

	cout << "isSolved : "<< boardArr1D.isSolved() << endl;
	cout << "Total number of moves " << boardArr1D.getNumOfMove() << endl;
}
void driverBoardArray2D()
{
	int size;

	cout << "BOARDARRAY2D CLASS" << endl;

	cout << "Please enter the problem size" << endl;

	cin >> size;

	BoardArray2D boardArr2D;
	
	boardArr2D.setSize(size,size);
	boardArr2D.print();

	cout << "Move:R" << endl;
	boardArr2D.move('R',1);
	boardArr2D.print();

	cout << "Move:L" << endl;
	boardArr2D.move('L',1);
	boardArr2D.print();

	cout << "Move:U" << endl;
	boardArr2D.move('U',1);
	boardArr2D.print();

	cout << "Move:D" << endl;
	boardArr2D.move('D',1);
	boardArr2D.print();

	cout << "Please enter file name for writing file" << endl;
	string fileName2D;
	cin >> fileName2D;
	boardArr2D.writeToFile(fileName2D);

	cout << "Please enter file name for reading file" << endl;
	cin >> fileName2D;
	boardArr2D.readFromFile(fileName2D);

	cout << "Move:R" << endl;
	boardArr2D.move('R',1);
	boardArr2D.print();

	cout << "Move:L" << endl;
	boardArr2D.move('L',1);
	boardArr2D.print();

	cout << "Reset" << endl;
	boardArr2D.reset();

	cout << "isSolved : "<< boardArr2D.isSolved() << endl;
}

bool driverGlobalFunction(AbstractBoard* ab[], int size)
{
	bool flagForMove = false;
	for(int i = 0 ; i < size; ++i)
	{
		ab[i]->print();
	}


	for(int i = 0; i < size-1; ++i)
	{
		AbstractBoard* temp_ab = ab[i]->clone();

		auto moveControl = temp_ab->move('U',1);
		if(moveControl && (*temp_ab == *ab[i + 1]))
			flagForMove = true;

		delete temp_ab;
		temp_ab = ab[i]->clone();

		moveControl = temp_ab->move('D',1);
		if(moveControl && (*temp_ab == *ab[i + 1]))
			flagForMove = true;

		delete temp_ab;
		temp_ab = ab[i]->clone();

		moveControl = temp_ab->move('R',1);
		if(moveControl && (*temp_ab == *ab[i + 1]))
			flagForMove = true;

		delete temp_ab;
		temp_ab = ab[i]->clone();

		moveControl = temp_ab->move('L',1);
		if(moveControl && (*temp_ab == *ab[i + 1]))
			flagForMove = true;


		delete temp_ab;

	}

	return flagForMove;


}
bool initializeBoardsForGlobalFunc(int i)
{
	if(i == 0) // vector 3 lu valid
	{
		BoardVector vec1(3,3);
		vec1.setSize(3,3);
		BoardVector vec2 = vec1;
		
		while(true)
		{
			auto a = vec2.move('R',1);
			if(a){
				break;
			}
			a = vec2.move('L',1);
			if(a){
				break;
			}
			a = vec2.move('U',1);
			if(a){
				break;
			}
			a = vec2.move('D',1);
			if(a){
				break;
			}
		}

		BoardVector vec3 = vec2;

		while(true)
		{
			auto a = vec3.move('R',1);
			if(a){
				break;
			}
			a = vec3.move('L',1);
			if(a){
				break;
			}
			a = vec3.move('U',1);
			if(a){
				break;
			}
			a = vec3.move('D',1);
			if(a){
				break;
			}
		}

		AbstractBoard* abstractBoard[3] = {&vec1, &vec2, &vec3};
		return driverGlobalFunction(abstractBoard,3);
	}

	if(i == 1) //vektor 2 li invalid
	{
		BoardVector vec1(3,3);
		vec1.setSize(3,3);
		BoardVector vec2(3,3);
		vec2.setSize(3,3);
		AbstractBoard* abstractBoard[2] = {&vec1, &vec2};
		return driverGlobalFunction(abstractBoard,2);
	}

	if(i == 2) //board1d 2 li valid
	{
		BoardArray1D vec1;
		vec1.setSize(4,4);
		BoardArray1D vec2 = vec1;
		
		while(true)
		{
			auto a = vec2.move('R',1);
			if(a){
				break;
			}
			a = vec2.move('L',1);
			if(a){
				break;
			}
			a = vec2.move('U',1);
			if(a){
				break;
			}
			a = vec2.move('D',1);
			if(a){
				break;
			}
		}

		AbstractBoard* abstractBoard[2] = {&vec1, &vec2};
		return driverGlobalFunction(abstractBoard,2);
	}

	if(i == 3) // board1d 3 lu valid
	{
		BoardArray1D vec1;
		vec1.setSize(3,3);
		BoardArray1D vec2 = vec1;
		
		while(true)
		{
			auto a = vec2.move('R',1);
			if(a){
				break;
			}
			a = vec2.move('L',1);
			if(a){
				break;
			}
			a = vec2.move('U',1);
			if(a){
				break;
			}
			a = vec2.move('D',1);
			if(a){
				break;
			}
		}

		BoardArray1D vec3 = vec2;

		while(true)
		{
			auto a = vec3.move('R',1);
			if(a){
				break;
			}
			a = vec3.move('L',1);
			if(a){
				break;
			}
			a = vec3.move('U',1);
			if(a){
				break;
			}
			a = vec3.move('D',1);
			if(a){
				break;
			}
		}

		AbstractBoard* abstractBoard[3] = {&vec1, &vec2, &vec3};
		return driverGlobalFunction(abstractBoard,3);
	}

	if(i == 4) //board1d 2 li invalid
	{
		BoardArray1D vec1;
		vec1.setSize(4,4);
		BoardArray1D vec2;
		vec2.setSize(4,4);

		AbstractBoard* abstractBoard[2] = {&vec1, &vec2};
		return driverGlobalFunction(abstractBoard,2);
	}
}

int main(const int argc, const char* argv[])
{
	srand(time(NULL));

	cout << "FUNCTION TESTS" << endl;

	int choice;
	cout << "1 - BoardVector" << endl;
	cout << "2 - BoardArray1D" << endl;
	cout << "3 - BoardArray2D" << endl;
	cout << "4 - GLOBAL FUNCTION" << endl;

	cin >> choice;

	cout << "Your Choice : " << choice << endl;

	switch(choice)
	{
		case 1 : 
		driverBoardVector();
		break;		
		case 2 : 
		driverBoardArray1D();
		break;	
		case 3 : 
		driverBoardArray2D();
		break;	
		case 4 : 
		{
			for(int i = 0; i < 5; ++i)
			{
				auto a = initializeBoardsForGlobalFunc(i);
				
				if(a)
					cout << "Valid sequence of moves" << endl;
				else
					cout << "Not valid sequence of moves" << endl;
			}
			break;	
		}

		default:
		cout << "Invalid choice" << endl;
	}
	return 0;
}