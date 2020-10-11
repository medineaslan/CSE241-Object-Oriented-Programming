#include <iostream>

#include "boardarray2d.h"

using std :: cout;
using std :: endl;

namespace NPuzzleGame
{
	BoardArray2D :: BoardArray2D()
	{
		
	}
	bool BoardArray2D :: setSize(int rowValue, int columnValue)
	{
		bool returnValue = false;

		row = rowValue;
		column = columnValue;

		board2D = new int*[row];

		for (int i = 0; i < row; i++)
			board2D[i] = new int[column];

			initialize2DBoard();
			returnValue = true;

		return returnValue;
	}
	BoardArray2D :: BoardArray2D(const BoardArray2D& other)
		:row(other.getRow()), column(other.getColumn())
	{
		int **board2D = new int*[row];

		for(int i = 0; i < row; ++i)
		board2D[i] = new int[column];

	    for(int i=0; i < row; i++){
	    	for(int j=0; j < column; j++){
	    		board2D[i][j] = other.board2D[i][j];
	    	}
	    }
	}
	int BoardArray2D :: getRow()const
	{
		return row;
	}
	int BoardArray2D :: getColumn()const
	{
		return column;
	}
	int BoardArray2D :: operator () (int index_i, int index_j)
	{
		return board2D[index_i][index_j];
	}
	bool BoardArray2D :: isSolved()
	{
		int temp_array[row*column], i, j, size1;
		decltype(size1) size2;
		auto k = 0, game_over = 0,controller = 0;

		size1 = row;
		size2 = column;

		if(getFileBoardControl() == true){
			for(i=0; i < size1; i++){
				for(j=0; j < size2; j++){
					temp_array[k] = board2D[i][j];
					k++;
				}
			}
			for(i=0; i < (size1 * size2) - 2; i++){
				if(temp_array[i] < temp_array[i+1])
					game_over++;
			}
			if(game_over == ((size1 * size2) - 2) && temp_array[(size1 * size2) - 1] == -1)
				return true;
			else
				return false ;
		}
		else{
			k=0;
			game_over = 0;
			for(i=0; i < size1; i++){
				for(j=0; j < size2; j++){
					if(board2D[i][j] != 0){
						temp_array[k] = board2D[i][j];
						k++;
						controller++;
					}
				}
			}
			for(i=0; i < controller-2; i++){
				if(temp_array[i] < temp_array[i+1]){
					game_over++;
				}
			}
			if(game_over == (controller - 2) && temp_array[controller - 1] == -1)
				return true;
			else
				return false ;
		}
	}
	void BoardArray2D ::  writeToFile(const string fileName)
	{
		int i, j;
		ofstream save_file;
		save_file.open(fileName.c_str());

		if(getFileBoardControl()){ 
			for(i=0; i < row; i++){
				for(j=0; j < column; j++){
					if(board2D[i][j] == -1 ){
						save_file << "bb";
						if(j != column - 1)
							save_file << " ";
					}
					else{
						if(board2D[i][j] != -1){
							if(board2D[i][j] <= 9){
								save_file << "0" << board2D[i][j];
							}
							else{
								save_file << board2D[i][j];
							}
							if(j != (column-1))
								save_file << " ";	
						}
					}
				}
				if(i != row - 1){
					save_file << endl ;
				}
			}
			save_file << endl;
		}
		else{ //Came from file.
			for (i=0; i < row; ++i){
				for (j=0; j < column; ++j){
					if(board2D[i][j] != -1){
						int digit = calculate_digit_number(board2D[i][j]);
						if(digit < 2){
							save_file << "0" << board2D[i][j];
							if(j != column - 1)
								save_file << " ";
						}
						else{
							save_file << board2D[i][j] ;
							if(j != column - 1)
								save_file << " ";
						}
					}
					else{
						save_file << "bb" ;
						if(j != column - 1)
							save_file << " ";
					}
				}
				save_file << endl;
			}
		}
		print();
		save_file.close();
	}
	void BoardArray2D :: readFromFile(const string fileName)
	{
		int my_line_number = 0, my_total_space = 0;
		ifstream input_file;
		string line, load_file;
		load_file = fileName;
		input_file.open(load_file.c_str());

		while(getline(input_file,line)){ //Read lines from file
			my_line_number++; // Calculate line number.
			for(int i = 0; i < line.size(); ++i){
				if(line.at(i) == ' ')
					my_total_space++; //Calculate all spaces in the file.
			}
		}
		input_file.close();

		row = my_line_number;
		column = (my_total_space / row) + 1;

		setSize(row,column);

		input_file.open(load_file.c_str());

		int i, j;
		char temp_ch_array[row][column * 2];

		for(i=0; i < row; i++){ //Read elements from the file.
			for(j=0; j < column * 2; j++){
				input_file >> temp_ch_array[i][j];
			}
		}
		input_file.close();

		for(i=0; i < row; i++){ //Convert string to integer.
			for(j=0; j < column * 2; j=j+2){
				char  first_index, second_index;
				string str_1, str_2, string_number;
				int number;

				first_index = temp_ch_array[i][j];
				second_index = temp_ch_array[i][j + 1];
				if(first_index == 'b') //Assign -1 for space.
					number = -1;
				else{
					str_1 = str_1 + first_index; 
					str_2 = str_2 + second_index;
					string_number = str_1 + str_2;

					number = stoi(string_number);
				}
				board2D[i][j/2] = number;
			}
		}
		setFileBoardControl(false); //file_board_control setting to false.
		print();
	}
	void BoardArray2D :: reset()
	{
		if(getFileBoardControl()){ 
			int i=0, j=0, k;

			for(k=1; k <= (row * column); k++){
				if(k == (row * column)){
					board2D[row-1][column-1] = -1;
				}
				else{
					if(k % (row) == 0){
						board2D[i][j] = k;
						i++;
						j=0;
					}
					else{
						board2D[i][j] = k;
						j++;
					}
				}	
			}
		}
		else{ //Came from file.
			int my_number = 1, i, j;
			for(i=0; i < row; i++){ //Takes final board.
				for(j=0; j < column; j++){
					if(board2D[i][j] != 0){
						board2D[i][j] = my_number; 
						my_number++;
					}
					if(i == row - 1 && j == column - 1)
						board2D[i][j] = -1;
				}
			}
		}
		print();
	}
	bool BoardArray2D :: move(const char move, int controller)
	{
		///File board control false ise dosyadan okudum.
		int i, j, row_num;
		decltype(i) column_num;

		row_num = row;
		column_num = column;

		if(move == 'R'){ //The empty cell is moved in the right direction.
			for(i=0; i < row_num; i++){
				for(j=0; j < column_num && controller == 1; j++){
					if(board2D[i][j] == -1){	
						if(j != (column_num - 1) && board2D[i][j+1] != 0){ //If the right side does not exceed the board limit, movement is made.
							int right_temp_number;

							right_temp_number = board2D[i][j+1];
							board2D[i][j+1] = -1;
							board2D[i][j] = right_temp_number;
							controller = 0;

							return true;
						}
					}
				}
			}
		}
		else if(move == 'L'){ //The empty cell is moved in the left direction.
			for(i=0; i < row_num; i++){
				for(j=0; j < column_num; j++){
					if(board2D[i][j] == -1){
						if(j != 0 && board2D[i][j-1] != 0){ //If the left side does not exceed the board limit, movement is made.
							int left_temp_number;

							left_temp_number = board2D[i][j-1];
							board2D[i][j-1] = -1;
							board2D[i][j] = left_temp_number;

							return true;
						}
					}
				}
			}
		}
		else if(move == 'U'){ //The empty cell is moved in the up.
			for(i=0; i < row_num; i++){
				for(j=0; j < column_num; j++){
					if(board2D[i][j] == -1){
						if(i != 0 && board2D[i-1][j] != 0){ //If the up side does not exceed the board limit, movement is made.
							int up_temp_number;

							up_temp_number = board2D[i-1][j];
							board2D[i-1][j] = -1;
							board2D[i][j] = up_temp_number;

							return true;
						}
					}
				}
			}
		}
		else if(move == 'D'){ //The empty cell is moved in the down.
			for(i=0; i < row_num && controller == 1; i++){
				for(j=0; j < column_num && controller == 1; j++){
					if(board2D[i][j] == -1){			
						if(i != (row_num - 1) && board2D[i+1][j] != 0){ //If the down side does not exceed the board limit, movement is made.
							int down_temp_number;

							down_temp_number = board2D[i+1][j];
							board2D[i+1][j] = -1;
							board2D[i][j] = down_temp_number;
							controller = 0;

							return true;
						}
					}
				}
			}
		}
		return false;
	}
	bool BoardArray2D :: operator == (const AbstractBoard& other)
	{
		BoardArray2D* newBoard = (BoardArray2D*)&other;

		for(int i=0; i < row; i++){
			for(int j=0; j < column; j++){
				if(board2D[i][j] != newBoard->board2D[i][j])
					return false;
			}
		}
		return true;
	}
	void BoardArray2D :: initialize2DBoard()
	{
		int i, j, k, controller_array[row*column];
		decltype(i) random;
		auto l=0,flag = 1,controller = 0;

		for(i=0; i < row; i++){
			for(j=0; j < column; j++){
				flag = 1;
				random = 1 + rand() % ((row * column));
				for(k=0; k < controller; k++){
					if(random == controller_array[k])
						flag = 0;	
				}
				if(flag == 1){
					controller_array[l] = random;
					board2D[i][j] = random;
					controller++;
					l++;	
				}
				else if(flag == 0){
					if (j == 0){
						i--;
						j = (column-1);		
					}
					else
						j--;
				}
			}
		}	
		for(i=0; i < row; i++){
			for(j=0; j < column; j++){
				if(board2D[i][j] == (row * column))
					board2D[i][j] = -1;
			}
		}
	}
	
	void BoardArray2D :: print()
	{
		int i;
		decltype(i) j;

		if(getFileBoardControl()){
			for(i=0; i < row; i++){
				for(j=0; j < column; j++){
					if(board2D[i][j] == -1)
						cout << " \t";
					else
						cout << board2D[i][j] << "\t" ;	
				}
				cout << endl ;
			}
			cout << endl;
		}
		else{
			for (i=0; i < row; ++i) {
				for (j=0; j < column; ++j) {
					if(board2D[i][j] != -1){
						int digit = calculate_digit_number(board2D[i][j]);
						if(digit < 2)
							cout << "0" << board2D[i][j] << " ";
						else
							cout << board2D[i][j] << " ";
					}
					else
						cout << "bb" << " ";	
				}
				cout << endl;
			}
			cout << endl;
		}
	}
	BoardArray2D& BoardArray2D :: operator =(const BoardArray2D& other)
	{
		row = other.row;
		column = other.column;

		for(int i = 0; i < row; ++i)
		{
			delete [] board2D[i];
		}
		delete [] board2D;

		board2D = new int*[row];

		for (int i = 0; i < row; i++)
			board2D[i] = new int[column];

		for(int i = 0; i < row; i++){
			for(int j=0; j < column; j++){
				board2D[i][j] = other.board2D[i][j];
			}
		}
		return *this;
	}
	BoardArray2D :: ~BoardArray2D ( )
	{
		for(int i = 0; i < row; ++i)
		{
			delete [] board2D[i];
		}
		delete [] board2D;
	}
}
